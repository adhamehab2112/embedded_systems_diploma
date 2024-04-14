/*
 * main.c
 *
 *  Created on: Jul 4, 2023
 *      Author: adham
 */
#include"includes/stm32_f103_x6.h"
#include "MCAL/GPIO/GPIO.h"
#include"HAL/LCD/LCD.h"
#include"HAL/KEYPAD/KEYPAD.h"
#include "MCAL/EXTI/EXTI.h"

uint8_t IRQ_Flag = 0 ;

void wait(uint32_t time)
{
	uint32_t i , j;

	for( i=0 ; i<time ; i++)
		for(j=0 ; j<255 ; j++);
}

//call back function
void EXTI9_CallBack(void)
{
	IRQ_Flag = 1 ;

}

int val1 = 3 ;
int val2 = 7 ;
int val3 = 0 ;
int main()
{
	//ENABLE CLOCK
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();
	//EXTI CONFIG
	EXTI_Config_t MyExti ;
	MyExti.EXT_PIN_CONFIG = EXTI9PB9 ;
	MyExti.TRIGGER_CASE = EXTI_RISING_EDGE ;
	MyExti.PTR_CALLBACK_FUN = EXTI9_CallBack ;
	MyExti.IRQ_EN = IRQ_ENABLE ;
	MCAL_EXTI_Init(&MyExti);
	IRQ_Flag = 1 ;


	__asm("nop\n\tnop"); /*No operation -> 1 clk cycle */
	// add val3 , val1,val2

	__asm("add %0 , %1 ,%2"
			: "=r" (val3)
			: "r" (val1) ,   // (,) for more than one
			  "r" (val2));
	/*
	 * Specifier :
	 * 			r --> replace by a GPR (most used)
	 * 			w --> floating point
	 * 			i --> integer const
	 * 			x --> any kind of operand
	 * */
	/*
	 * Constraint Modifiers
	 * 				= --> write only operand  (most used )
	 * 				+ --> both read and write (default could be empty --> most used)
	 * 				& --> write only and can not be used
	 * */

	__asm("nop\n\tnop");


	while(1)
	{

		if(IRQ_Flag)
		{

			IRQ_Flag = 0 ;
		}
		/*axf*/

	}
	return 0 ;
}

