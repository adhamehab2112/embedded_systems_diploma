/*
 * Created on: Apr 22, 2024
 * Author: Adhoum
 * Creating My own RTOS
 */
#include"core_cm3.h"
#include<stdio.h>
#include <string.h>
#include"Scheduler.h"
#include"AE_RTOS_FIFO.h"

void wait(uint32_t time)
{
	uint32_t i , j;

	for( i=0 ; i<time ; i++)
		for(j=0 ; j<255 ; j++);
}

Task_ref_t Task1 , Task2 , Task3 ;
unsigned char task1LED , task2LED , task3LED;
void task1_fun()
{
	while(1)
	{
		task1LED ^= 1 ;
	}
}
void task2_fun()
{
	while(1)
	{
		task2LED ^= 1 ;
	}
}
void task3_fun()
{
	while(1)
	{
		task3LED ^= 1 ;
	}
}


int main()
   {
	// HW_Init (CLK-RCC)
	HW_Init();
	// RTOS Initialization
	if(RTOS_Init() == E_NOK)
	{
		while(1);
	}
	Task1.StackSize = 1024 ;
	Task1.ptr_TaskEntery = task1_fun ;
	Task1.TaskPriority = 3 ;
	strcpy(Task1.TaskName,"task_1");
	Task2.StackSize = 1024 ;
	Task2.ptr_TaskEntery = task2_fun ;
	Task2.TaskPriority = 3 ;
	strcpy(Task2.TaskName,"task_2");
	Task3.StackSize = 1024 ;
	Task3.ptr_TaskEntery = task3_fun ;
	Task3.TaskPriority = 3 ;
	strcpy(Task3.TaskName,"task_3");

	RTOS_Create_Task(&Task1);
	RTOS_Create_Task(&Task2);
	RTOS_Create_Task(&Task3);
	RTOS_Activate_Task(&Task1);
	RTOS_Activate_Task(&Task2);
	RTOS_Activate_Task(&Task3);
	RTOS_StartOS();
	while(1)
	{



	}
	return 0 ;
}










