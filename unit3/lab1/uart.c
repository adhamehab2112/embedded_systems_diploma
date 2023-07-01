#include"uart.h"
#define UART0DR *((volatile unsigned int *)((unsigned int *)0x101F1000)) // same as in your mind that's for warning
void UART_Send_String(unsigned char *ptr_to_string)
{
	while(*ptr_to_string != '\0')
	{
		UART0DR = (unsigned int)(*ptr_to_string); // type cast to unsigned int from unsigned char
		ptr_to_string++;
	}
}