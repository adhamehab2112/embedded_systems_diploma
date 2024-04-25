/*
 * Scheduler.h
 *
 *  Created on: Apr 22, 2024
 *      Author: adham
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_
#include"CortexMx_Os_Porting.h"


/************************************** Os Errors Enumeration ********************************/
typedef enum {
	E_NOK ,
	E_OK ,
	ReadyQueue_init_error ,
	StackSize_exceeds
}Os_Error_State_t;
/********************************************************************************************/

/************************************** Tasks reference struct ******************************/
typedef struct {
	unsigned int StackSize ;
	unsigned char TaskPriority ;
	void (*ptr_TaskEntery)(void);
	enum {
		AutoStart_Dis ,
		AutoStart_En
	}AutoStart_State;
	unsigned int _S_PSP_Task  ;
	unsigned int _E_PSP_Task  ;
	unsigned int *Current_PSP ;
	unsigned char TaskName[30];
	enum{
		Suspended ,
		Waiting   ,
		ready     ,
		running
	}TaskState;
	struct{
			enum {
				Blocking_Dis ,
				Blocking_En
			}BlockingState;
			unsigned int Ticks_Count ;
	}TimeWaiting;
}Task_ref_t;



/************************************** APIs Header *****************************************/
void 				 OS_SVC_Services(int *args);
void 				 Os_SVC_Set(int SVC_ID);
Os_Error_State_t	 RTOS_Init(void);
Os_Error_State_t 	 RTOS_Create_Task(Task_ref_t *Ptr_task);


#endif /* INC_SCHEDULER_H_ */
