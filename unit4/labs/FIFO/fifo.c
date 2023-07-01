/*
 * fifo.c
 *
 *  Created on: May 2, 2023
 *      Author: adham
 */
#include<stdint.h>
#define elemType uint32_t
#define size 5
elemType buffer[size];

typedef struct {
	elemType *head ;
	elemType *tail ;
	elemType *base ;
	uint32_t count ;
	uint32_t length ;
}FIFO_buff_t;

