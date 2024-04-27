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

/********************************** Private Os Control Structure *********************/
struct {
	Task_ref_t *OsTasks[100]		;
	unsigned int _S_MSP				;
	unsigned int _E_MSP				;
	unsigned int PSP_Task_Locator	;
	unsigned int NoActiceTasks		;
	Task_ref_t *CurreuntTask		;
	Task_ref_t *NexttTask			;
	enum {
		Os_Suspended ,
		Os_Running
	}OSMode;
}OS_Control;

/********************************** Private Os Services Enumeration ********************/
typedef enum {
	SVC_ActivateTask	,
	SVC_TerminateTask	,
	SVC_TaskWait
}SVC_OS_Services_t;

/*******************************Private Os Global variables **************************/
FIFO_Buf_t ReadyQueue ;
Task_ref_t *ReadyQueue_FIFO[100]; //Array of tasks
Task_ref_t RTOS_IDLE_Task ;
unsigned char IdleTaskLed ;

/*************************************************************************************/

/****************************** PendSV Handler****************************************/
__attribute ((naked))void PendSV_Handler()
{
	/*Switch context and Switch restore*/
	//==================================
	//Save context of the Current task :

	//1-we have to get the current task PSP value (from CPU REGSITERS -> CPU pushed xpsr->r0)
	OS_GET_PSP(OS_Control.CurreuntTask->Current_PSP);
	//2-use PSP to store R4-R11 (save them using current_psp pointer)
	OS_Control.CurreuntTask->Current_PSP -- ;
	__asm volatile("mov %0,r4" :"=r"(*(OS_Control.CurreuntTask->Current_PSP)) );
	OS_Control.CurreuntTask->Current_PSP -- ;
	__asm volatile("mov %0,r5" :"=r"(*(OS_Control.CurreuntTask->Current_PSP)) );
	OS_Control.CurreuntTask->Current_PSP -- ;
	__asm volatile("mov %0,r6" :"=r"(*(OS_Control.CurreuntTask->Current_PSP)) );
	OS_Control.CurreuntTask->Current_PSP -- ;
	__asm volatile("mov %0,r7" :"=r"(*(OS_Control.CurreuntTask->Current_PSP)) );
	OS_Control.CurreuntTask->Current_PSP -- ;
	__asm volatile("mov %0,r8" :"=r"(*(OS_Control.CurreuntTask->Current_PSP)) );
	OS_Control.CurreuntTask->Current_PSP -- ;
	__asm volatile("mov %0,r9" :"=r"(*(OS_Control.CurreuntTask->Current_PSP)) );
	OS_Control.CurreuntTask->Current_PSP -- ;
	__asm volatile("mov %0,r10" :"=r"(*(OS_Control.CurreuntTask->Current_PSP)) );
	OS_Control.CurreuntTask->Current_PSP -- ;
	__asm volatile("mov %0,r11" :"=r"(*(OS_Control.CurreuntTask->Current_PSP)) );

	//==================================
	//Restore context of the next task
	OS_Control.CurreuntTask = OS_Control.NexttTask ;
	OS_Control.NexttTask = NULL ;
	/*Manual Context Restore*/
	__asm volatile("mov %0,r11" :"=r"(*(OS_Control.CurreuntTask->Current_PSP)) );
	OS_Control.CurreuntTask->Current_PSP ++ ;
	__asm volatile("mov %0,r10" :"=r"(*(OS_Control.CurreuntTask->Current_PSP)) );
	OS_Control.CurreuntTask->Current_PSP ++ ;
	__asm volatile("mov %0,r9" :"=r"(*(OS_Control.CurreuntTask->Current_PSP)) );
	OS_Control.CurreuntTask->Current_PSP ++ ;
	__asm volatile("mov %0,r8" :"=r"(*(OS_Control.CurreuntTask->Current_PSP)) );
	OS_Control.CurreuntTask->Current_PSP ++ ;
	__asm volatile("mov %0,r7" :"=r"(*(OS_Control.CurreuntTask->Current_PSP)) );
	OS_Control.CurreuntTask->Current_PSP ++ ;
	__asm volatile("mov %0,r6" :"=r"(*(OS_Control.CurreuntTask->Current_PSP)) );
	OS_Control.CurreuntTask->Current_PSP ++ ;
	__asm volatile("mov %0,r5" :"=r"(*(OS_Control.CurreuntTask->Current_PSP)) );
	OS_Control.CurreuntTask->Current_PSP ++ ;
	__asm volatile("mov %0,r4" :"=r"(*(OS_Control.CurreuntTask->Current_PSP)) );
	OS_Control.CurreuntTask->Current_PSP ++ ;
	OS_SET_PSP(OS_Control.CurreuntTask->Current_PSP); /*Restore context of new task after finishing handler*/
	__asm volatile("BX LR"); /*Execution return xode*/

}

/*************************************************************************************/

/************************************** Private Os APIs ******************************/
/**================================================================
* @Fn    		: RTOS_PrivCreate_MainStack
* @brief 		: This function is used to Specify the os main stack in SRAM
* @param [in] 	: void
* @param [out] 	: void
*===================================================================*/
void RTOS_PrivCreate_MainStack()
{
	OS_Control._S_MSP =  &_estack ;
	OS_Control._E_MSP = OS_Control._S_MSP - 3072 ; //3K Main StacK size
	OS_Control.PSP_Task_Locator = OS_Control._E_MSP - 8 ;// 8 byte Alignment
	if(OS_Control._E_MSP <= _eheap )
	{
		while(1); //exceeds the stack size in SRAM
	}
}

/**================================================================
* @Fn    		: RTOS_IdleTask
* @brief 		: Rtos IDLE task that executes NOP instruction (1 clk cycle )
* @param [in] 	: void
* @param [out] 	: void
*===================================================================*/
void RTOS_privIdleTask()
{
	while(1)
	{
		IdleTaskLed ^= 1;
		__asm("NOP");
	}
}

void RTOS_PrivCreate_Stack(Task_ref_t *Ptr_task)
{
	/*Create Task Fram*/
	/*============================
	 * --> done by CPU
	 *xpsr
	 *pc = next instruction to be execute in task
	 *lr = return address for the task caller before switching
	 * r12
	 * r4
	 * r3
	 * r2
	 * r1
	 * r0
===================
	 * -> done Manual (save/restore)
	 * r5
	 * r6
	 * r7
	 * r8
	 * r9
	 * r10
	 * r11
	 * ===========================
	 *
	 * */
	/*we have to create this context stack as dummy data for the first time*/
	Ptr_task->Current_PSP = Ptr_task->_S_PSP_Task ;
	Ptr_task->Current_PSP--;
	*(Ptr_task->Current_PSP) = 0x01000000;     //dummy xPSR value
	Ptr_task->Current_PSP--;
	*(Ptr_task->Current_PSP) = (unsigned int)Ptr_task->ptr_TaskEntery; // dummy pc
	Ptr_task->Current_PSP--;
	*(Ptr_task->Current_PSP) = 0xFFFFFFFD; // dummy lr (exec_ret code)
	for(char itr=0 ; itr<13 ; itr++)
	{
		Ptr_task->Current_PSP--;
		*(Ptr_task->Current_PSP) = 0; //GPRs dummy data
	}

}
/**================================================================
* @Fn    		: RTOS_Tasks_Sorting
* @brief 		: this function is used to sort Tasks according to priorities
* @param [in] 	: void
* @param [out] 	: void
*===================================================================*/
void RTOS_Tasks_Sorting()
{
	unsigned int i , j ,noTasks ;
	noTasks = OS_Control.NoActiceTasks;
	Task_ref_t *Task_temp ;
	for(i=0 ; i<(noTasks-1) ; i++)
	{
		for(j=0 ; j<noTasks-i-1 ; j++)
		{
			if(OS_Control.OsTasks[j]->TaskPriority > OS_Control.OsTasks[j+1]->TaskPriority)
			{
				Task_temp = OS_Control.OsTasks[j] ;
				OS_Control.OsTasks[j] = OS_Control.OsTasks[j+1];
				OS_Control.OsTasks[j+1] = Task_temp  ;
			}
		}
	}
	/*Now the OS_Control.OsTasks array is sorted from higher than lower priority*/
}
/**================================================================
* @Fn    		: RTOS_Update_SchedulerTable
* @brief 		:
* @param [in] 	: void
* @param [out] 	: void
*===================================================================*/
void RTOS_Update_SchedulerTable()
{
	/*1-Scheduler Table (OS_Control.OSTasks[100]) bubble sort based on priority*/
	RTOS_Tasks_Sorting();
	/*2-Free ready queue*/
	Task_ref_t *emptyingBuffer = NULL ;
	while(FIFO_dequeue(&ReadyQueue, &emptyingBuffer) != FIFO_EMPTY); /*Pointer to Pointer*/
	/*3-Update ready queue*/
	unsigned int itr = 0 ;
	Task_ref_t *Ptr_Task ;
	Task_ref_t *Ptr_NextTask ;
	while(itr < OS_Control.NoActiceTasks)
	{
		/*Remember that the Tasks are sorted based on Priority*/
		Ptr_Task = OS_Control.OsTasks[itr];
		Ptr_NextTask = OS_Control.OsTasks[itr+1];
		if(Ptr_Task->TaskState != Suspended)
		{
			if(Ptr_NextTask->TaskState == Suspended)
			{
				FIFO_enqueue(&ReadyQueue, Ptr_Task);
				Ptr_Task->TaskState = Ready ;
				break;
			}
			if(Ptr_Task->TaskPriority < Ptr_NextTask->TaskPriority)
			{
				/*Lower number in priority == Highest priority*/
				FIFO_enqueue(&ReadyQueue, Ptr_Task);
				Ptr_Task->TaskState = Ready ;
				break;
			}
			else if(Ptr_Task->TaskPriority == Ptr_NextTask->TaskPriority)
			{
				/*Lower number in priority == Highest priority*/
				FIFO_enqueue(&ReadyQueue, Ptr_Task);
				Ptr_Task->TaskState = Ready ; /*Round Robin case*/
			}

		}

		itr++;
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
	/*1-If ready queue is empty => no task && OS_Control.CurrentTask not suspended ==> there is only
	 * 1 task that is executing now (not the idle)*/
	if(ReadyQueue.counter == 0 && OS_Control.CurreuntTask->TaskState != Suspended)
	{
		OS_Control.CurreuntTask->TaskState = Running ;
		FIFO_enqueue(&ReadyQueue, OS_Control.CurreuntTask);
		OS_Control.NexttTask = OS_Control.CurreuntTask ; /*execute the only existed task*/
	}
	else
	{
		FIFO_dequeue(&ReadyQueue, &OS_Control.NexttTask);
		OS_Control.NexttTask->TaskState = Running ;
		if(OS_Control.CurreuntTask->TaskPriority == OS_Control.NexttTask->TaskPriority && OS_Control.CurreuntTask->TaskState != Suspended)
		{
			/*Added again the current task for round robin alg*/
			FIFO_enqueue(&ReadyQueue, OS_Control.CurreuntTask);
			OS_Control.CurreuntTask->TaskState = Ready ;
			/*now Next-> running and current->ready*/
		}

	}

}
/**================================================================
* @Fn    		: OS_SVC_Service
* @brief 		: This function used to execute certain OS service based on SVC #Number
* @param [in] 	: Address of caller SP (MSP or PSP)
* @param [out] 	: void
*===================================================================*/
void OS_SVC_Services(int *args)
{
	/********************** Handler Mode ************************/
	/*args = r0 -> MSP or PSP*/
	//OS_SVC Stack end -> r0
	//OS_SVC Stack : old r0-r1-r2-r3-r12-lr-pc-xpsr
	unsigned char SVC_Number ;
	SVC_Number = *((unsigned char*)(((unsigned char*)args[6]) - 2 ));
	switch(SVC_Number)
	{
				/*Os Services Selection*/

	case SVC_ActivateTask  : // Activate Task
	case SVC_TerminateTask : // Terminate Task
							/*1-Update Scheduler Table
							 * 2-Update ready queue*/
							RTOS_Update_SchedulerTable();
							/*3-Os Running State*/
							if(OS_Control.OSMode == Os_Running)
							{
								if(strcmp(OS_Control.CurreuntTask->TaskName,"Idle Task") !=0 )
								{	/**IDLE Task will be executed manually**/
									/*4-Decide which Next*/
									RTOS_Select_Next_Task();
									/*5-Trigger Pendsv (Context switch/restore)*/
									// will be a naked function (to not create a new stack)
									trigger_OS_PendSV();
								}
							}

							break;
	case SVC_TaskWait :
							break;
	}


}
/**================================================================
* @Fn    		: Os_SVC_Set
* @brief 		: This function used to Make the CPU interrupt itself to operate a certain service
* @param [in] 	: Service Number (Supervisor call ID)
* @param [out] 	: void
*===================================================================*/
void Os_SVC_Set(int SVC_ID)
{

	switch(SVC_ID)
	{
		case SVC_ActivateTask: //Activate Task
				__asm("SVC #0x00");
				break;
		case SVC_TerminateTask : //Terminate Task
				__asm("SVC #0x01");
				break;
		case SVC_TaskWait : //Task Wait
				__asm("SVC #0x02");
				break;
	}

}
/*************************************************************************************/


/************************************** Public Os APIS *******************************/

/**================================================================
* @Fn    		: RTOS_Init
* @brief 		: This function used to initialize the OS (Update Mode - Create MStsck - Create Ready queue - Config IDLE task )
* @param [in] 	: void
* @param [out] 	: void
*===================================================================*/
Os_Error_State_t RTOS_Init(void)
{
		Os_Error_State_t initState = E_OK ;
		/*1-Update the OS mode*/
		OS_Control.OSMode = Os_Suspended;
		/*2-Specify the Main Stack*/
		RTOS_PrivCreate_MainStack();
		/*3-Create OS Ready Queue*/
		if(FIFO_init(&ReadyQueue, ReadyQueue_FIFO, 100) != FIFO_NO_ERROR)
		{
			initState += ReadyQueue_init_error ;
		}
		/*Create IDLE Task*/
		strcpy(RTOS_IDLE_Task.TaskName , "Idle Task");
		RTOS_IDLE_Task.TaskPriority = 255 ; //Higher number lower priority
		RTOS_IDLE_Task.ptr_TaskEntery = RTOS_privIdleTask;
		RTOS_IDLE_Task.StackSize = 300 ;
		initState  += RTOS_Create_Task(&RTOS_IDLE_Task);

		return initState ;
}
/**================================================================
* @Fn    		: RTOS_Create_Task
* @brief 		: This function used to create Task
* @param [in] 	: Task reference
* @param [out] 	: Os_Error_State_t
*===================================================================*/
Os_Error_State_t RTOS_Create_Task(Task_ref_t *Ptr_task)
{
	Os_Error_State_t error_state = E_OK ;
	/*1-create Task stack*/
	/*2-check if the task size will not exceeds the stack size*/
	/*3- Align 8 bytes*/
	Ptr_task->_S_PSP_Task = OS_Control.PSP_Task_Locator ;
	Ptr_task->_E_PSP_Task = Ptr_task->_S_PSP_Task - Ptr_task->StackSize ;
	if(Ptr_task->_E_PSP_Task <= &_eheap)
	{
		error_state = StackSize_exceeds;
	}
	OS_Control.PSP_Task_Locator = (Ptr_task->_E_PSP_Task - 8) ;
	/*Initialize the TASK frame (used in context switch and restore =>xpsr-pc-ldr-r12-r3-r2-r1-r0)*/
	/*By switching context using os we have to store/restore all registers (r5->r11) manually */
	/*each created function must have preinitialized registers values and task frame*/
	RTOS_PrivCreate_Stack(Ptr_task);
	/*4- Add task to scheduler table*/
	OS_Control.OsTasks[OS_Control.NoActiceTasks] = Ptr_task;
	OS_Control.NoActiceTasks++;
	/*5-update Task state*/
	Ptr_task->TaskState = Suspended ;
	return error_state;
}
/**================================================================
* @Fn    		: RTOS_Activate_Task
* @brief 		: This function used to Activate certain task
* @param [in] 	: Task reference
* @param [out] 	: Os_Error_State_t
*===================================================================*/
Os_Error_State_t RTOS_Activate_Task(Task_ref_t *Ptr_task)
{
	Os_Error_State_t error_state = E_OK ;
	/*1-Update the Task State*/
	Ptr_task->TaskState = Waiting ;
	/*2-Call SVC Set (Activate ID)*/
	Os_SVC_Set(SVC_ActivateTask);

	return error_state ;

}
/**================================================================
* @Fn    		: RTOS_Terminate_Task
* @brief 		: This function used to Terminate certain task
* @param [in] 	: Task reference
* @param [out] 	: Os_Error_State_t
*===================================================================*/
Os_Error_State_t RTOS_Terminate_Task(Task_ref_t *Ptr_task)
{
	Os_Error_State_t error_state = E_OK ;
	/*1-Update the Task State*/
	Ptr_task->TaskState = Suspended;
	/*2-Call SVC Set (Activate ID)*/
	Os_SVC_Set(SVC_TerminateTask);

	return error_state ;

}
/**================================================================
* @Fn    		: RTOS_StartOS
* @brief 		: This function used to Terminate certain task
* @param [in] 	: void
* @param [out] 	: Os_Error_State_t
*===================================================================*/
Os_Error_State_t RTOS_StartOS()
{
	Os_Error_State_t error_state = E_OK ;
	OS_Control.OSMode = Os_Running ;
	OS_Control.CurreuntTask = &RTOS_IDLE_Task ;
	RTOS_Activate_Task(&RTOS_IDLE_Task);
	System_Start_Ticker();
	OS_SET_PSP(OS_Control.CurreuntTask->Current_PSP);
	OS_SWITCH_SP_TO_PSP	;
	OS_SWITCH_TO_UNPRIV ;
	RTOS_IDLE_Task.ptr_TaskEntery();

	return error_state ;
}

