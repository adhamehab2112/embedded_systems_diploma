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

int Var_1 = 0 ;
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
	// MOV r0 , #0xff then o/p r0 to c variable called Var_1 of type int (local or global)
	__asm("mov %0 , #0xff"
			:"=r" (Var_1) ); // 1st column : o/p parameters (c takes from asm)
	/*
	 * __asm("Instruction Pattern"
	 * 			: "Specifier" ( c variable name) -> output parameters );
	*/

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

