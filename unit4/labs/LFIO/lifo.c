/*
 * lifo.c
 *
 *  Created on: May 2, 2023
 *      Author: adham
 */
#include"lifo.h"
LIFO_state_t LIFO_init(LIFO_buf_t *lifo_buff , elemType *buff , uint32_t length)
{
	if(buff == NULL)
	{
		return LIFO_not_exist;
	}
	lifo_buff->count = 0 ;
	lifo_buff->lenght = length ;
	lifo_buff->base = buff ;
	lifo_buff->head = buff ;
	return LIFO_no_error ;

}
LIFO_state_t LIFO_add_element_push(LIFO_buf_t *lifo_buff , elemType item )
{
	if(lifo_buff->base == NULL || lifo_buff->head == NULL)
		return LIFO_not_exist ;
	if(lifo_buff->count == lifo_buff->lenght)
		return LIFO_is_full ;
	*lifo_buff->head = item ;

	lifo_buff->head++ ;
	lifo_buff->count ++ ;
	return LIFO_no_error ;
}
LIFO_state_t LIFO_get_element_pop(LIFO_buf_t *lifo_buff , elemType *p_to_get)
{
	if(lifo_buff->base == NULL || lifo_buff->head == NULL)
		return LIFO_not_exist ;
	if(lifo_buff->count == 0 )
		return LIFO_is_empty ;
	lifo_buff->head--;
	*p_to_get = *(lifo_buff->head);

	lifo_buff->count-- ;
	return LIFO_no_error ;
}

