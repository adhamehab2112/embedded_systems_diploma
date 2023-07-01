/*
 * lifo.h
 *
 *  Created on: May 2, 2023
 *      Author: adham
 */

#ifndef LIFO_H_
#define LIFO_H_
#include<stdint.h>

#define elemType uint32_t
#define size 10

elemType LIFO_buff[size];

//define the structure of LIFO
typedef struct {
	uint32_t lenght ; // size of stack
	uint32_t count ; // number of elements in stack
	elemType *base ; // base address of stack
	elemType *head ;// top of stack
}LIFO_buf_t;

//define the LIFO states
typedef enum {
	LIFO_no_error ,
	LIFO_is_full ,
	LIFO_is_empty ,
	LIFO_not_exist
}LIFO_state_t;

//define the LIFO APIs
LIFO_state_t LIFO_init(LIFO_buf_t *lifo_buff , elemType *buff , uint32_t length);
LIFO_state_t LIFO_add_element_push(LIFO_buf_t *lifo_buff , elemType item );
LIFO_state_t LIFO_get_element_pop(LIFO_buf_t *lifo_buff , elemType *p_to_get);

#endif /* LIFO_H_ */
