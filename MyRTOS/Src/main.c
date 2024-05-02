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

Task_ref Task1, Task2, Task3, Task4;
unsigned char T1_Led, T2_Led, T3_Led, T4_Led;
void Task1_func()
{
	static int counter = 0 ;
	while(1)
	{
		T1_Led ^=1;
		counter++;
		if(counter==30)
		{
			RTOS_ActivateTask(&Task4);

		}
		RTOS_Task_Wait(100,&Task1);
	}
}

void Task2_func()
{
	while(1)
	{
		T2_Led ^=1;
		RTOS_Task_Wait(300,&Task2);
	}
}

void Task3_func()
{
	while(1)
	{
		T3_Led ^=1;
		RTOS_Task_Wait(500,&Task3);
	}
}

void Task4_func()
{
	static int counter = 0 ;
	while(1)
	{
		T4_Led ^=1;
		RTOS_Task_Wait(1000, &Task4);
	}
}

int main(void)
{
	Hardware_init();
	RTOS_init();

	Task1.Stack_Size = 1024;
	Task1.P_TaskEntery = Task1_func;
	Task1.Priority = 3;
	Task1.Task_State = Suspended;
	strcpy(Task1.Task_name,"task1");

	Task2.Stack_Size = 1024;
	Task2.P_TaskEntery = Task2_func;
	Task2.Priority = 3;
	Task2.Task_State = Suspended;
	strcpy(Task2.Task_name,"task2");

	Task3.Stack_Size = 1024;
	Task3.P_TaskEntery = Task3_func;
	Task3.Priority = 3;
	Task3.Task_State = Suspended;
	strcpy(Task3.Task_name,"task3");


	Task4.Stack_Size = 1024;
	Task4.P_TaskEntery = Task4_func;
	Task4.Priority = 1;
	Task4.Task_State = Suspended;
	strcpy(Task4.Task_name,"task4");

	RTOS_CreateTask(&Task1);
	RTOS_CreateTask(&Task2);
	RTOS_CreateTask(&Task3);
	RTOS_CreateTask(&Task4);


	RTOS_ActivateTask(&Task1);
	RTOS_ActivateTask(&Task2);
	RTOS_ActivateTask(&Task3);

	RTOS_StartOS();

	while(1)
	{

	}
}


