/*
 * in this lab we will create a function that swaps between CPU modes (priv-unpriv)
 */
#include"includes/stm32_f103_x6.h"
#include "MCAL/GPIO/GPIO.h"
#include"HAL/LCD/LCD.h"
#include"HAL/KEYPAD/KEYPAD.h"
#include "MCAL/EXTI/EXTI.h"

uint8_t IRQ_Flag = 0 ;

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

//call back function
void EXTI9_CallBack(void)
{
	IRQ_Flag = 1 ;
	Switch_CPU_Access_Mode(privlege);
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
	IRQ_Flag = 1 ;
	/*The CPU mode is priv by default*/
	Switch_CPU_Access_Mode(unprivelge);


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

