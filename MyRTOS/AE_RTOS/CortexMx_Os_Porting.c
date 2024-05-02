/*********************************************************************************************************
 * ********************************************************************************************************
AUTHOR  : ADHAM EHAB
MICRO   : STM32F32F103
LAYER   : Services Layer
DRIVER  : AE_RTOS
File    : CortexMx_Os_Porting.c
Version :1.0
********************************************************************************************************
*********************************************************/

#include"CortexMx_Os_Porting.h"
void HardFault_Handler()
{

}
void MemManage_Handler()
{

}
void BusFault_Handler()
{

}
void UsageFault_Handler()
{

}

void trigger_OS_PendSV()
{
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;

}

unsigned char SysTickLed;
void SysTick_Handler()
{
	SysTickLed ^= 1;

	//watch tasks waiting time
	RTOS_Update_TaskTime();

	//Decide what next
	RTOS_Select_Next_Task();

	//trigger OS_PendSV (Switch context/Restore)
	trigger_OS_PendSV();
}

__attribute ((naked))void SVC_Handler()
{
	__asm("tst lr, #4 \n\t"
			"ITE EQ \n\t"
			"mrseq r0,MSP \n\t"
			"mrsne r0,PSP \n\t"
			"B OS_SVC_Service");
}

void Hardware_init()
{
	//intialize clock tree (RCC -> SysTick Timer & CPU) 8 MHZ
	//init HW
	//Clock Tree
	//RCC Default values makes CPU Clock & SysTick Timer clock = 8 MHZ
	//Initializes the System Timer and its interrupt, and starts the System Tick Timer.


	// decrease PendSV interrupt priority to be smaller than or equal SysTick Timer
	__NVIC_SetPriority(PendSV_IRQn, 15);
}

void Start_Systick()
{
	/* 8 MHZ
	  * 1 count -> 0.125 us
	  * X count -> 1 ms
	  * X = 8000 count
	  */
	SysTick_Config(8000);

}
