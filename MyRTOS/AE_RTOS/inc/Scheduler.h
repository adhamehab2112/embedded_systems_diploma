/*
 * Scheduler.h
 *
 *  Created on: Apr 22, 2024
 *      Author: adham
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_
#include"CortexMx_Os_Porting.h"

/************************************** Tasks reference struct ******************************/
typedef enum{
	Suspended,
	Ready,
	Waiting,
	Running
}T_State;

typedef struct{
	enum{
		Blocking_Disable,
		Blocking_Enable
	}Blocking;
	unsigned int Ticks_count;
}Time_wait;

typedef struct{

	unsigned int Stack_Size;
	unsigned char Priority;
	void (*P_TaskEntery)(void);
	unsigned int _S_PSP_Task;
	unsigned int _E_PSP_Task;
	unsigned int* Current_PSP;
	T_State Task_State;
	char Task_name[30];
	Time_wait TimeWait;

}Task_ref;

typedef enum {
	NOError,
	Ready_Queue_init_error,
	Task_exceeded_StackSize
}RTOS_errorID;
/************************************** APIs Header *****************************************/
RTOS_errorID 		RTOS_init();
RTOS_errorID 		RTOS_CreateTask(Task_ref *Task_ref);
void 				RTOS_ActivateTask(Task_ref* T_ref);
void 				RTOS_TerminalTask(Task_ref* T_ref);
void 				RTOS_StartOS();
void				RTOS_Task_Wait(unsigned int	NumOfTicks , Task_ref *Task_ref);


#endif /* INC_SCHEDULER_H_ */
