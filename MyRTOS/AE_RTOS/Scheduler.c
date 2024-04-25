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

/************************************** Os Control Structure ******************************/
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
		Os_Ready
	}OSMode;
}OS_Control;

/*******************************Private Os Global variables **************************/
FIFO_Buf_t ReadyQueue ;
Task_ref_t *ReadyQueue_FIFO[100]; //Array of tasks
Task_ref_t RTOS_IDLE_Task ;

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
	OS_Control._S_MSP = &_estack ;
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
	*Ptr_task->Current_PSP = 0x01000000;     //dummy xPSR value
	Ptr_task->Current_PSP--;
	*Ptr_task->Current_PSP = (unsigned int)Ptr_task->ptr_TaskEntery; // dummy pc
	Ptr_task->Current_PSP--;
	*Ptr_task->Current_PSP = 0xFFFFFFFD; // dummy lr (exec_ret code)
	for(char itr=0 ; itr<13 ; itr++)
	{
		Ptr_task->Current_PSP--;
		*Ptr_task->Current_PSP = 0; //GPRs dummy data
	}

}

/*************************************************************************************/


/************************************** Public Os APIS *******************************/
/**================================================================
* @Fn    		: OS_SVC_Service
* @brief 		: This function used to execute certain OS service based on SVC #Number
* @param [in] 	: Address of caller SP (MSP or PSP)
* @param [out] 	: void
*===================================================================*/
void OS_SVC_Services(int *args)
{
	/*args = r0 -> MSP or PSP*/
	//OS_SVC Stack end -> r0
	//OS_SVC Stack : old r0-r1-r2-r3-r12-lr-pc-xpsr
	unsigned char SVC_Number ;
	SVC_Number = *((unsigned char*)(((unsigned char*)args[6]) - 2 ));
	switch(SVC_Number)
	{
				/*Os Services Selection*/

	case 1 : // Activate Task
			break;
	case 2 : // Terminate Task
			break;
	case 3 :
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
		case 1 : //Activate Task
				__asm("SVC #0x01");
				break;
		case 2 : //Terminate Task
				__asm("SVC #0x02");
				break;
		case 3 : //Os PendSV
				__asm("SVC #0x03");
				break;
	}

}
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
	if(Ptr_task->_E_PSP_Task <= _eheap)
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
