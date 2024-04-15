/*
 * in this lab we will work on the ARM CPU Stack (MSP-PSP)
 */
#include"includes/stm32_f103_x6.h"
#include "MCAL/GPIO/GPIO.h"
#include"HAL/LCD/LCD.h"
#include"HAL/KEYPAD/KEYPAD.h"
#include "MCAL/EXTI/EXTI.h"


// Os Macros
#define TaskA_Stack_Size 			100 //100byte
#define TaskB_Stack_Size 			100 //100byte
#define OS_SET_PSP(add)				__asm volatile("MOV r0,%0 \n\t MSR PSP,r0" : :"r" (add))
#define OS_SP_TO_PSP				__asm volatile("MRS r0,CONTROL \n\t MOV r1,#0x02 \n\t ORR r0,r0,r1 \n\t MSR CONTROL,r0") // We need to write on the Control reg bit[1] ==> 1
#define Os_Generate_Exception		__asm volatile("SVC #3")
#define OS_SP_TO_MSP				__asm volatile("MRS r0,CONTROL \n\t MOV r1,#0x05 \n\t AND r0,r0,r1 \n\t MSR CONTROL,r0")

/***** All are initialized by default zero *****/
uint8_t TaskA_flag , TaskB_flag , IRQ_Flag = 0 ;

//Main Stack Pointer
extern int _estack; // extern the symbole from linker script
unsigned int _S_MSP = &_estack  ;
unsigned int _E_MSP ;



//TaskA Process Stack Pointer
uint32_t _S_PSP_TA ;
uint32_t _E_PSP_TA ;



//TaskB Process Stack Pointer
uint32_t _S_PSP_TB ;
uint32_t _E_PSP_TB ;



typedef enum  {
	privlege,
	unprivelge
}CPU_Acess_Levels;

void Switch_CPU_Access_Mode(CPU_Acess_Levels level)
{
	switch(level)
	{
	case privlege :
		//Clear Bit[0] in Control register
		__asm("MRS r3,CONTROL \n\t"
			  "LSR r3,r3,#0x1 \n\t"
			  "LSL r3,r3,#0x1 \n\t"
			  "MSR CONTROL,r3");

		break;
	case unprivelge :
		//Set Bit[1] in Control register
		__asm("MRS r3,CONTROL \n\t"
			  "ORR r3,r3,#0x1 \n\t"
			  "MSR CONTROL,r3");
	}
}

void wait(uint32_t time)
{
	uint32_t i , j;

	for( i=0 ; i<time ; i++)
		for(j=0 ; j<255 ; j++);
}

void SVC_Handler()
{
	Switch_CPU_Access_Mode(privlege);
}

//call back function
void EXTI9_CallBack(void)
{
	/*In this isr we will decide which task will execute */
	/*
	 * 1st rising edge --> Task A
	 * 2nd rising edge --> Task B
	 * */
	if(IRQ_Flag == 0)
	{
		TaskA_flag = 1 ;
		IRQ_Flag = 1 ;
	}
	else if (IRQ_Flag == 1)
	{
		TaskB_flag = 1 ;
		IRQ_Flag = 0 ;
	}


}


int taskA(int a , int b , int c )
{
	return a+b+c ;
}
int taskB(int a , int b , int c , int d  )
{
	return a+b+c ;
}




void OsMain()
{
	/* Dummy Os Main Function */
	//////Stack Configuration////////
	// -VE --> Descending Stack Mechanism

	//1- Main Stack size as configured in LAB
	_E_MSP = (_S_MSP - 512) ;

	//2-TaskA Stack size as configured in LAB
	_S_PSP_TA = (_E_MSP - 8) ;
	_E_PSP_TA = (_S_PSP_TA - TaskA_Stack_Size);

	//3-TaskB Stack size as configured in LAB
	_S_PSP_TB = (_E_PSP_TA - 8) ;
	_E_PSP_TB = (_S_PSP_TB - TaskB_Stack_Size);

	while(1)
	{
		__asm("nop");
		if(TaskA_flag ==1)
		{
			// Set PSP points to the top of TaskA stack
				OS_SET_PSP(_S_PSP_TA);
			// Sp --> PSP instade of MSP
				OS_SP_TO_PSP;
			// Switch CPU mode to unprivileged mode
				Switch_CPU_Access_Mode(unprivelge);
			// call the task
			TaskA_flag = taskA(1, 2, 3) ;
			// Switch from Unpriv to priv
			Os_Generate_Exception;
			// Sp --> MSP
			OS_SP_TO_MSP;
		}
		else if (TaskB_flag==1)
		{
			// Set PSP points to the top of TaskA stack
				OS_SET_PSP(_S_PSP_TB);
			// Sp --> PSP instade of MSP
				OS_SP_TO_PSP;
			// Switch CPU mode to unprivileged mode
				Switch_CPU_Access_Mode(unprivelge);
			// call the task
			TaskB_flag = taskB(1, 2, 3 , 4);
			// Switch from Unpriv to priv
			Os_Generate_Exception;
			// Sp --> MSP
			OS_SP_TO_MSP;
		}
	}
}
int main()
{
	//ENABLE CLOCK
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();
	//EXTI CONFIG
	EXTI_Config_t MyExti ;
	MyExti.EXT_PIN_CONFIG = EXTI9PB9 ;
	MyExti.TRIGGER_CASE = EXTI_RISING_EDGE ;
	MyExti.PTR_CALLBACK_FUN = EXTI9_CallBack ;
	MyExti.IRQ_EN = IRQ_ENABLE ;
	MCAL_EXTI_Init(&MyExti);

	OsMain();

	while(1)
	{

		if(IRQ_Flag)
		{

			IRQ_Flag = 0 ;
		}
		/*axf*/

	}
	return 0 ;
}

