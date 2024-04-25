/*********************************************************************************************************
 * ********************************************************************************************************
AUTHOR  : ADHAM EHAB
MICRO   : STM32F32F103
LAYER   : Services Layer
DRIVER  : AE_RTOS
File    : AE_RTOS_FIFO.c
Version :1.0
********************************************************************************************************
*********************************************************/


#include"AE_RTOS_FIFO.h"

/**================================================================
* @Fn    		: FIFO_init
* @brief 		: This function is used Intialize the FIFO
* @param [in] 	: Pointer to element of type FIFO buffer - Pointer to Task - FIFO length
* @param [out] 	: Buffer_status
*===================================================================*/
Buffer_status FIFO_init (FIFO_Buf_t* fifo,element_type* buff , unsigned int length){

	if(!buff )
		return FIFO_NULL;

	fifo->base = buff ;
	fifo->head = fifo->base ;
	fifo->tail = fifo->base ;
	fifo->length = length;
	fifo->counter=0;

	return FIFO_NO_ERROR;

}

/* *********************************** */
/**================================================================
* @Fn    		: FIFO_enqueue
* @brief 		: This function is used to add elements the FIFO
* @param [in] 	: Pointer to element of type FIFO buffer - Pointer to Task that will be added in the queue
* @param [out] 	: Buffer_status
*===================================================================*/

Buffer_status FIFO_enqueue (FIFO_Buf_t* fifo,element_type item){

	/* fifo null*/

	if (!fifo->base || !fifo->length)
		return FIFO_NULL;
	/*fifo is full*/

	/* fifo full */
	if ((fifo->head == fifo->tail) && (fifo->counter == fifo->length))
		return FIFO_FULL;

	*(fifo->tail)=item;
	fifo->counter++;

	/*for circular fifo again */

	/* circular enqueue */
	if (fifo->tail == (((unsigned int)fifo->base + (4*fifo->length )) - 4 ))
		fifo->tail = fifo->base;
	else
		fifo->tail++;

	return FIFO_NO_ERROR;


}

/* *********************************** */
/**================================================================
* @Fn    		: FIFO_dequeue
* @brief 		: This function is used to remove elements the FIFO
* @param [in] 	: Pointer to element of type FIFO buffer - Pointer to Task that will be renoved in the queue
* @param [out] 	: Buffer_status
*===================================================================*/

Buffer_status FIFO_dequeue (FIFO_Buf_t* fifo, element_type* item){
	/* check fifo valid */
	if (!fifo->base || !fifo->length)
		return FIFO_NULL;

	/* fifo empty */
	if (fifo->head == fifo->tail)
		return FIFO_EMPTY;



	*item = *(fifo->head);
	fifo->counter--;

	/* circular dequeue */
	if (fifo->head == (((unsigned int)fifo->base + (4*fifo->length )) - 4 ))
		fifo->head = fifo->base;
	else
		fifo->head++;

	return FIFO_NO_ERROR;
}




/* *********************************** */
/**================================================================
* @Fn    		: FIFO_is_full
* @brief 		: This function is used to check if the FIFO is full or no
* @param [in] 	: Pointer to element of type FIFO buffer
* @param [out] 	: Buffer_status
*===================================================================*/

Buffer_status FIFO_is_full (FIFO_Buf_t* fifo){

	if(!fifo->head || !fifo->base || !fifo->tail)
		return FIFO_NULL;
	if(fifo->counter == fifo->length)
		return FIFO_FULL;

	return FIFO_NO_ERROR;
}
