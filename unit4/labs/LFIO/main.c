/*
 * main.c
 *
 *  Created on: May 2, 2023
 *      Author: adham
 */
#include"lifo.h"
#include<stdio.h>
#include<stdlib.h>
LIFO_buf_t stack_test1; // define a stack
elemType stack_buff1[5]; // define your data containar using static allocation
LIFO_buf_t stack_test2;

int main() {
	uint8_t i ;
	elemType temp=0 ;
	LIFO_init(&stack_test1, stack_buff1 , 5); // create LIFO1
	elemType *stack_buff2 = (elemType *) malloc(5 * sizeof(elemType)); // define your data containar using dynamic allocation
	LIFO_init(&stack_test2, stack_buff2 , 5); // create LIFO1
	for(i=0 ; i<6 ; i++)
	{

		switch(LIFO_add_element_push(&stack_test1 , i))
		{
		case LIFO_no_error :printf("LFIO stack_test1 add %d done \n",i); break;


		case LIFO_is_full :printf("LFIO stack_test1 is full \n"); break ;


		case LIFO_not_exist :printf("LFIO stack_test1 not exist \n"); break ;

		case LIFO_is_empty :printf("LFIO stack_test1 is empty \n"); break ;
		}


	}
	for(i=0 ; i<5 ; i++)
	{
		switch(LIFO_get_element_pop(&stack_test1 , &temp))
		{
		case LIFO_no_error :printf("LFIO stack_test1 get %d done \n",temp); break ;

		case LIFO_is_empty :printf("LFIO stack_test1 is empty \n"); break ;

		case LIFO_not_exist :printf("LFIO stack_test1 not exist \n"); break;

		case LIFO_is_full :printf("LFIO stack_test1 is full \n"); break;
		}
	}
	return 0 ;
}

