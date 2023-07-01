#include"uart.h"
#include<stdio.h>
unsigned char string_buffer[100]={"learn-in-depth-adham"};
void main(void)
{
	 UART_Send_String(string_buffer);
}