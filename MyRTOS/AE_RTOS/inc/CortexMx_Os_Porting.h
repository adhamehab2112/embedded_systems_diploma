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
extern int _estack ;
extern int _eheap  ;
#define  MainStackSize  3072

#define SWITCH_CPU_AccessLevel_privileged 	  __asm volatile("mrs  r3, CONTROL  \n\t lsr   r3,r3,#0x1   \n\t lsl   r3,r3,#0x1    \n\t msr  CONTROL, r3")
#define SWITCH_CPU_AccessLevel_unprivileged   __asm volatile("mrs  r3, CONTROL  \n\t orr   r3,r3,#0x1   \n\t msr  CONTROL, r3")

#define OS_SET_PSP(address) __asm volatile ("mov r0, %0 \n\t msr PSP, r0"  : : "r" (address))
#define OS_GET_PSP(address) __asm volatile ("mrs r0, PSP \n\t mov %0, r0"  : "=r" (address))

#define OS_SWITCH_SP_to_PSP __asm volatile ("mrs r0, CONTROL \n\t mov r1, #0x02 \n\t orr r0,r0,r1 \n\t msr CONTROL, r0 ")  //set bit 1 in CONTROL register to one
#define OS_SWITCH_SP_to_MSP __asm volatile ("mrs r0, CONTROL \n\t mov r1, #0x05 \n\t and r0,r0,r1 \n\t msr CONTROL, r0 ")  //set bit 1 in CONTROL register to zero

void Hardware_init();
void trigger_OS_PendSV();
void Start_Systick();

#endif /* INC_CORTEXMX_OS_PORTING_H_ */
