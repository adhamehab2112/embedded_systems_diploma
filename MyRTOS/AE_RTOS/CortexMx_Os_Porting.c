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

/******************		Faults Exceptions Handler		***************/

void HardFault_Handler()
{
	while(1);
}
void MemManage_Handler()
{
	while(1);
}
void BusFault_Handler()
{
	while(1);
}
void UsageFault_Handler()
{
	while(1);
}
/*********************************************************************/

/******************		Supervisor call handler		*****************/
__attribute((naked)) void SVC_Handler()
{
	//Switch_CPU_Access_Mode(privilege);
	/*
	 * ---> We will make this SVC_Hnadler as assembly ==> No caller stack pushing
	 * 1- Know we were in which stack MSP/PSP -> r0
	 * 2- call a c-function that take a pointer as arg (r0)
	 * */
	__asm("TST LR,#0x4 \n\t"
		  "ITE EQ \n\t"
		  "MRSEQ r0,MSP \n\t"
		  "MRSNE r0,PSP \n\t"
		  "B OS_SVC_Services");


}
/**********************		Pendsv handler	*********************/
void PendSV_Handler()
{
	/*will be used in context switching*/
}
/**================================================================
* @Fn    		: HW_Init
* @brief 		: This function used to initialize the cpu core peripherals on which the Os depends
* @param [in] 	: void
* @param [out] 	: void
*===================================================================*/
void HW_Init()
{
	/*1-Initialize Clock Tree (RCC-> System Timer , RCC->CPU Clock 8Mhz(default) )*/
	// 8Mhz
	// 1 Count -> 0.125 us (Ticker)
	// x Count -> 1ms ---> To configure periodic interrupt
	// x = 8000 count

}
