/*********************************************************************************************************
 * ********************************************************************************************************
AUTHOR  : ADHAM EHAB
MICRO   : STM32F32F103
LAYER   : Services Layer
DRIVER  : AE_RTOS
File    : CortexMx_Os_Porting.h
Version :1.0
********************************************************************************************************
*********************************************************/

#ifndef INC_CORTEXMX_OS_PORTING_H_
#define INC_CORTEXMX_OS_PORTING_H_

 #include"core_cm3.h"

/************************** Stack Top Symbol *************************************************/
extern unsigned int _estack ;
extern unsigned int _eheap  ;
/************************** Core Processor Stack Pointer Operations****************************/
#define OS_SET_PSP(add)					__asm volatile("MOV r0,%0 \n\t MSR PSP,r0" : :"r" (add))
#define OS_GET_PSP(add)					__asm volatile("MRS r0,PSP \n\t MOV %0,r0" :"=r"(add))



#define OS_SWITCH_SP_TO_PSP				__asm volatile("MRS r0,CONTROL \n\t MOV r1,#0x02 \n\t ORR r0,r0,r1 \n\t MSR CONTROL,r0") // We need to write on the Control reg bit[1] ==> 1
#define OS_SWITCH_SP_TO_MSP				__asm volatile("MRS r0,CONTROL \n\t MOV r1,#0x05 \n\t AND r0,r0,r1 \n\t MSR CONTROL,r0")


/************************** Core Processor CPU access Levels*********************************/
/* Bit[0] in Control register
 * 0-> Priv
 * 1-> Unpriv
 * */
#define OS_SWITCH_TO_PRIV				__asm("MRS r3,CONTROL \n\t" \
										"LSR r3,r3,#0x1 \n\t"		\
										"LSL r3,r3,#0x1 \n\t"		\
										"MSR CONTROL,r3")
#define OS_SWITCH_TO_UNPRIV				__asm("MRS r3,CONTROL \n\t" \
			  	  	  	  	  	  	  	"ORR r3,r3,#0x1 \n\t"		\
										"MSR CONTROL,r3")
/************************************** APIs Header *****************************************/
void trigger_OS_PendSV();
void System_Start_Ticker();

#endif /* INC_CORTEXMX_OS_PORTING_H_ */
