/*********************************************************************************************************
 * ********************************************************************************************************
AUTHOR  : ADHAM EHAB
MICRO   : STM32F32F103
LAYER   : Services Layer
DRIVER  : AE_RTOS
File    : Scheduler.c
Version :1.0
********************************************************************************************************
*********************************************************/

#include"Scheduler.h"
#include"AE_RTOS_FIFO.h"
/*******************************Private Os Global variables **************************/
Task_ref RTOS_IdleTask;
FIFO_Buf_t Ready_QUEUE ;
Task_ref* Ready_QUEUE_FIFO[100] ;
unsigned char IdleTaskLed;
/********************************** Private Os Services Enumeration ********************/
typedef enum{
	ActivateTask,
	TerminateTask,
	TaskWaitingTime
}SVC_ID;

/********************************** Private Os Modes Enumeration ********************/
typedef enum {
	OSSuspended,
	OSRunning
}OS_Modes;

/********************************** Private Os Control Structure *********************/
struct{
	Task_ref* OS_Tasks[100];
	unsigned int _S_MSP;
	unsigned int _E_MSP;
	unsigned int  PSP_TaskLocator;
	unsigned char NumberOfCreatedTask;
	Task_ref* Current_Task;
	Task_ref* Next_Task;
	OS_Modes OSModes;
}OS_Control;
/****************************** PendSV Handler****************************************/
__attribute ((naked)) PendSV_Handler()
{

	/* Save the Context of the Current Task?
	 * context saved on the stack
	 * by the CPU when entering Handler mode.
	 */

	//==============================================
	/* Get the Current Task "Current PSP"
	 * will save manually the addition frame of other general purpose registers
	 */
	OS_GET_PSP(OS_Control.Current_Task->Current_PSP);        //Current_Task for OS when OS in running mode

	OS_Control.Current_Task->Current_PSP--;
	__asm volatile("mov %0, r4 \n\t" : "=r" (*OS_Control.Current_Task->Current_PSP) );
	OS_Control.Current_Task->Current_PSP--;
	__asm volatile("mov %0, r5 \n\t" : "=r" (*OS_Control.Current_Task->Current_PSP) );
	OS_Control.Current_Task->Current_PSP--;
	__asm volatile("mov %0, r6 \n\t" : "=r" (*OS_Control.Current_Task->Current_PSP) );
	OS_Control.Current_Task->Current_PSP--;
	__asm volatile("mov %0, r7 \n\t" : "=r" (*OS_Control.Current_Task->Current_PSP) );
	OS_Control.Current_Task->Current_PSP--;
	__asm volatile("mov %0, r8 \n\t" : "=r" (*OS_Control.Current_Task->Current_PSP) );
	OS_Control.Current_Task->Current_PSP--;
	__asm volatile("mov %0, r9 \n\t" : "=r" (*OS_Control.Current_Task->Current_PSP) );
	OS_Control.Current_Task->Current_PSP--;
	__asm volatile("mov %0, r10 \n\t" : "=r" (*OS_Control.Current_Task->Current_PSP) );
	OS_Control.Current_Task->Current_PSP--;
	__asm volatile("mov %0, r11 \n\t" : "=r" (*OS_Control.Current_Task->Current_PSP) );

	/*Restore the Context of the next Task
	 * will restore manually frame of general purpose registers
	 * as these will not be automatically restored by the CPU.
	 */

	/*
	 * 	OS_SET_PSP(OS_Control.Next_Task->Current_PSP);
	 * 	This step After pushing the general purpose registers onto the stack manually,
	 * 	CPU PSP register will point to r0
	 */

	OS_Control.Current_Task = OS_Control.Next_Task ;
	OS_Control.Next_Task = NULL ;

	__asm volatile("mov r11, %0" : : "r" (*OS_Control.Current_Task->Current_PSP) );
	OS_Control.Current_Task->Current_PSP++;
	__asm volatile("mov r10, %0" : : "r" (*OS_Control.Current_Task->Current_PSP) );
	OS_Control.Current_Task->Current_PSP++;
	__asm volatile("mov r9, %0"  : : "r" (*OS_Control.Current_Task->Current_PSP) );
	OS_Control.Current_Task->Current_PSP++;
	__asm volatile("mov r8, %0"  : : "r" (*OS_Control.Current_Task->Current_PSP) );
	OS_Control.Current_Task->Current_PSP++;
	__asm volatile("mov r7, %0"  : : "r" (*OS_Control.Current_Task->Current_PSP) );
	OS_Control.Current_Task->Current_PSP++;
	__asm volatile("mov r6, %0"  : : "r" (*OS_Control.Current_Task->Current_PSP) );
	OS_Control.Current_Task->Current_PSP++;
	__asm volatile("mov r5, %0"  : : "r" (*OS_Control.Current_Task->Current_PSP) );
	OS_Control.Current_Task->Current_PSP++;
	__asm volatile("mov r4, %0"  : : "r" (*OS_Control.Current_Task->Current_PSP) );
	OS_Control.Current_Task->Current_PSP++;

	/*Update PSP register
	 *CPU read LR register -> Thread mode Restore:
	 * XPSR
	 * PC (Next Task Instruction which should be Run)
	 * LR (return register which is saved in CPU while TASk1 running before TaskSwitching)
	 * r12
	 * r4
	 * r3
	 * r2
	 * r1
	 * r0
	 */
	OS_SET_PSP(OS_Control.Current_Task->Current_PSP);
	/*
	 * __attribute ((naked)) means no stack frame set up by the compiler
	 * manually handle the exit from this Handler
	 * as the compiler will not automatically generate the exit code.
	 */
	__asm volatile("BX LR");
}


/*************************************************************************************/

/************************************** Private Os APIs ******************************/
/**================================================================
* @Fn    		: RTOS_IdleTask
* @brief 		: Rtos IDLE task that executes NOP instruction (1 clk cycle )
* @param [in] 	: void
* @param [out] 	: void
*===================================================================*/

void Idle_Task()
{
	while(1)
	{
		IdleTaskLed ^= 1;
		__asm("wfe");
	}
}

/**================================================================
* @Fn    		: RTOS_Create_MainStack
* @brief 		: This function is used to Specify the os main stack in SRAM
* @param [in] 	: void
* @param [out] 	: RTOS_errorID
*===================================================================*/
RTOS_errorID RTOS_Create_MainStack()
{
	RTOS_errorID error = NOError;

	// 3 KiloByte for MSP
	OS_Control._S_MSP = &_estack ;
	OS_Control._E_MSP = OS_Control._S_MSP - MainStackSize;
	OS_Control.PSP_TaskLocator = (OS_Control._E_MSP - 8);

	return error;

}
/**================================================================
* @Fn    		: RTOS_Create_TaskStack
* @brief 		: This function is used to Specify the process stack in SRAM
* @param [in] 	: void
* @param [out] 	: RTOS_errorID
*===================================================================*/
RTOS_errorID RTOS_Create_TaskStack(Task_ref* T_ref)
{
	RTOS_errorID error = NOError;


	/*Task Frame
	 * ======
	 * this context is saved and restored on stack by CPU (when enter/exit interrupt mode):
	 * XPSR
	 * PC (Next Task Instruction which should be Run)
	 * LR (return register which is saved in CPU while TASk1 running before TaskSwitching)
	 * r12
	 * r4
	 * r3
	 * r2
	 * r1
	 * r0
	 *====
	 *will push and pop manually the addition frame to save the other general purpose registers:
	 *r5, r6 , r7 ,r8 ,r9, r10,r11 (Saved/Restore)Manual
	 */

	T_ref->Current_PSP = T_ref->_S_PSP_Task;

	//DUMMY_XPSR should T =1
	T_ref->Current_PSP--;
	*(T_ref->Current_PSP) = 0x1000000;

	//PC
	T_ref->Current_PSP--;
	*(T_ref->Current_PSP) =  (unsigned int)T_ref->P_TaskEntery;

	//LR
	T_ref->Current_PSP--;
	//LR = 0xFFFFFFFD (EXC_RETURN)Return to thread with PSP
	*(T_ref->Current_PSP) = 0xFFFFFFFD;

	int i;
	for(i=0 ; i<13 ; i++ )
	{
		//rx
		T_ref->Current_PSP--;
		*(T_ref->Current_PSP) = 0;
	}

	return error;
}

/**================================================================
* @Fn    		: RTOS_Tasks_Sorting
* @brief 		: this function is used to sort Tasks according to priorities
* @param [in] 	: void
* @param [out] 	: void
*===================================================================*/
void RTOS_Tasks_Sorting()
{
	Task_ref* Temp;
	int i,j;
	for(i=0; i< (OS_Control.NumberOfCreatedTask - 1); i++)
		for(j=0; j< (OS_Control.NumberOfCreatedTask - 1 -i); j++)
		{
			if(OS_Control.OS_Tasks[j]->Priority > OS_Control.OS_Tasks[j+1]->Priority)
			{
				Temp = OS_Control.OS_Tasks[j];
				OS_Control.OS_Tasks[j]  = OS_Control.OS_Tasks[j+1];
				OS_Control.OS_Tasks[j+1]  = Temp;
			}
		}

}
/**================================================================
* @Fn    		: RTOS_Update_SchedulerTable
* @brief 		:
* @param [in] 	: void
* @param [out] 	: void
*===================================================================*/
//Handler mode
void RTOS_Update_SchedulerTable()
{
	RTOS_Tasks_Sorting();

	Task_ref* Temp = NULL;
	//Free Ready Queue
	while(FIFO_dequeue(&Ready_QUEUE, &Temp)!=FIFO_EMPTY);

	//Update Ready Queue
	Task_ref* Ptask;
	Task_ref* PnextTask;
	int i=0;
	while(i<OS_Control.NumberOfCreatedTask)
	{
		Ptask = OS_Control.OS_Tasks[i];
		PnextTask = OS_Control.OS_Tasks[i+1];
		if(Ptask->Task_State != Suspended)
		{
			if(PnextTask->Task_State == Suspended && (i+1) == (OS_Control.NumberOfCreatedTask-1))
			{
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->Task_State=Ready;
				break;
			}
			if(Ptask->Priority < PnextTask->Priority )
			{
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->Task_State=Ready;
				break;
			}else if(Ptask->Priority == PnextTask->Priority )
			{
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->Task_State=Ready;
			}
			else if(PnextTask == NULL)
			{
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->Task_State=Ready;
			}
		}
		i++;
	}
}

/**================================================================
* @Fn    		: RTOS_Select_Next_Task
* @brief 		: Select which task will execute
* @param [in] 	: void
* @param [out] 	: void
*===================================================================*/
void RTOS_Select_Next_Task()
{
	if(Ready_QUEUE.counter == 0 && OS_Control.Current_Task->Task_State != Suspended)
	{
		OS_Control.Current_Task->Task_State = Running;
		FIFO_enqueue(&Ready_QUEUE, OS_Control.Current_Task);

		/* This line is crucial for the next step, as it determines which task's
		 * information will be saved and which task will later restore its context.
		 */
		OS_Control.Next_Task = OS_Control.Current_Task;
	}else
	{
		FIFO_dequeue(&Ready_QUEUE, &OS_Control.Next_Task);
		OS_Control.Next_Task->Task_State = Running;


		if((OS_Control.Current_Task->Priority == OS_Control.Next_Task->Priority ) && ( OS_Control.Current_Task->Task_State != Suspended))
		{
			FIFO_enqueue(&Ready_QUEUE, OS_Control.Current_Task);
			OS_Control.Current_Task->Task_State = Ready;
		}
	}
}


/**================================================================
* @Fn    		: OS_SVC_Service
* @brief 		: This function used to execute certain OS service based on SVC #Number
* @param [in] 	: Address of caller SP (MSP or PSP)
* @param [out] 	: void
*===================================================================*/
//Handler Mode
void OS_SVC_Service(int *StackFramePointer)
{
	unsigned char SVC_number;
	SVC_number = *( (unsigned char*) ( (unsigned char*)StackFramePointer[6] )-2 ) ;
	switch(SVC_number)
	{
	case ActivateTask:
	case TerminateTask:
		//Update Sch table, Ready Queue
		RTOS_Update_SchedulerTable();
		//OS is in Running State
		if (OS_Control.OSModes == OSRunning)
		{
			//
			if(strcmp(OS_Control.Current_Task->Task_name,"idleTask") != 0)
			{
				//Decide what next
				RTOS_Select_Next_Task();
				//trigger OS_PendSV (Switch context/Restore)
				trigger_OS_PendSV();
			}
		}
		break;
	case TaskWaitingTime:
		RTOS_Update_SchedulerTable();

		break;
	}
}
/**================================================================
* @Fn    		: Os_SVC_Set
* @brief 		: This function used to Make the CPU interrupt itself to operate a certain service
* @param [in] 	: Service Number (Supervisor call ID)
* @param [out] 	: void
*===================================================================*/
//Thread Mode
void OS_SVC_Set(SVC_ID ID)
{
	switch(ID)
	{
	case ActivateTask:
		__asm("svc #0x00");
		break;
	case TerminateTask:
		__asm("svc #0x01");
		break;
	case TaskWaitingTime:
		__asm("svc #0x02");
		break;
	}
}

/**================================================================
* @Fn    		: RTOS_Update_TaskTime
* @brief 		: This function is used to be aware about timing ( This fun will be called in the systick handler)
* @param [in] 	: void
* @param [out] 	: void
*===================================================================*/
void RTOS_Update_TaskTime()
{
	for(unsigned int itr=0 ; itr < OS_Control.NumberOfCreatedTask ; itr++ )
	{
		if(OS_Control.OS_Tasks[itr]->TimeWait.Blocking == Blocking_Enable )
		{
			if(OS_Control.OS_Tasks[itr]->Task_State == Suspended)
		{
			OS_Control.OS_Tasks[itr]->TimeWait.Ticks_count-- ;
			if(OS_Control.OS_Tasks[itr]->TimeWait.Ticks_count == 0)
			{
				OS_Control.OS_Tasks[itr]->TimeWait.Blocking = Blocking_Disable ;
				OS_Control.OS_Tasks[itr]->Task_State = Waiting ;
				OS_SVC_Set(TaskWaitingTime);
			}
		}
		}

	}

}


/************************************** Public Os APIS *******************************/
/**================================================================
* @Fn    		: RTOS_Init
* @brief 		: This function used to initialize the OS (Update Mode - Create MStsck - Create Ready queue - Config IDLE task )
* @param [in] 	: void
* @param [out] 	: void
*===================================================================*/
RTOS_errorID RTOS_init()
{
	RTOS_errorID error = NOError;

	//Update OS mode
	OS_Control.OSModes = OSSuspended;

	//Specify the MAIN stack for OS
	RTOS_Create_MainStack();

	//Create OS ready Queue
	if (FIFO_init(&Ready_QUEUE, Ready_QUEUE_FIFO, 100) !=FIFO_NO_ERROR)
	{
		error += Ready_Queue_init_error ;
	}

	//Configure IDLE TASK
	strcpy(RTOS_IdleTask.Task_name, "idleTask");
	RTOS_IdleTask.Priority = 255;                	//lowest Priority (unsigned char -> 255)
	RTOS_IdleTask.P_TaskEntery = Idle_Task;
	RTOS_IdleTask.Stack_Size = 300;

	error += RTOS_CreateTask(&RTOS_IdleTask);

	return error;
}


/**================================================================
* @Fn    		: RTOS_Create_Task
* @brief 		: This function used to create Task
* @param [in] 	: Task reference
* @param [out] 	: Os_Error_State_t
*===================================================================*/
RTOS_errorID RTOS_CreateTask(Task_ref* T_ref)
{
	RTOS_errorID error = NOError;

	//create Its own PSP stack
	//check task stack size exceeded the PSP stack
	T_ref->_S_PSP_Task =  OS_Control.PSP_TaskLocator;
	T_ref->_E_PSP_Task = ( OS_Control.PSP_TaskLocator - T_ref->Stack_Size );

	//	-				-
	//	- _S_PSP_Task	-
	//	-	Task Stack	-
	//	- _E_PSP_Task	-
	//	-				-
	//	- _eheap		-
	//	-				-
	//

	if(T_ref->_E_PSP_Task < (unsigned int)(&(_eheap)))
	{
		//return Task_exceeded_StackSize;
	}

	//Aligned 8 Bytes spaces between Task PSP and other
	OS_Control.PSP_TaskLocator =  (T_ref->_E_PSP_Task - 8);

	//Initialize PSP Task Stack
	RTOS_Create_TaskStack(T_ref);

	//update sch Table
	OS_Control.OS_Tasks[OS_Control.NumberOfCreatedTask] = T_ref;
	OS_Control.NumberOfCreatedTask++;

	//Task state Update suspend
	T_ref->Task_State = Suspended;

	return error;
}


/**================================================================
* @Fn    		: RTOS_Activate_Task
* @brief 		: This function used to Activate certain task
* @param [in] 	: Task reference
* @param [out] 	: Os_Error_State_t
*===================================================================*/
void RTOS_ActivateTask(Task_ref* T_ref)
{
	T_ref->Task_State = Waiting;
	OS_SVC_Set(ActivateTask);
}
/**================================================================
* @Fn    		: RTOS_Terminate_Task
* @brief 		: This function used to Terminate certain task
* @param [in] 	: Task reference
* @param [out] 	: Os_Error_State_t
*===================================================================*/
void RTOS_TerminalTask(Task_ref* T_ref)
{
	T_ref->Task_State = Suspended;
	OS_SVC_Set(TerminateTask);
}
/**================================================================
* @Fn    		: RTOS_StartOS
* @brief 		: This function used to Terminate certain task
* @param [in] 	: void
* @param [out] 	: Os_Error_State_t
*===================================================================*/
void RTOS_StartOS()
{
	OS_Control.OSModes = OSRunning;
	//Set Default Task
	OS_Control.Current_Task = &RTOS_IdleTask;
	RTOS_ActivateTask(&RTOS_IdleTask);

	Start_Systick(); //1ms

	OS_SET_PSP(OS_Control.Current_Task->Current_PSP);
	OS_SWITCH_SP_to_PSP;
	SWITCH_CPU_AccessLevel_unprivileged;

	RTOS_IdleTask.P_TaskEntery();
}
/**================================================================
* @Fn    		: RTOS_Task_Wait
* @brief 		: This function used to Terminate suspend a task untill certain time
* @param [in] 	: void
* @param [out] 	: void
*===================================================================*/
void RTOS_Task_Wait(unsigned int NumOfTicks , Task_ref *Task_ref)
{
	Task_ref->TimeWait.Blocking = Blocking_Enable ;
	Task_ref->TimeWait.Ticks_count = NumOfTicks ;
	Task_ref->Task_State = Suspended ;
	OS_SVC_Set(TerminateTask);

}
