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

void CLK_init()
{
	// Enable Clock for GPIOA
	RCC_GPIOA_CLK_EN();
	// Enable Clock for GPIOB
	RCC_GPIOB_CLK_EN();
	//RCC ENABLE FOR EXTI
	RCC_AFIO_CLK_EN();
}

void GPIO_init()
{

	GPIO_Pin_Config_t PinCfg ;

	// CONFIGURE PA1 PP out
	PinCfg.GPIO_PIN_NUMBER = GPIO_PIN1 ;
	PinCfg.GPIO_PIN_MODE = GPIO_OUTPUT_PP ;
	MCAL_GPIO_Init(GPIOA, &PinCfg);

	//CONFIGURE PB1 as push-pull output
	PinCfg.GPIO_PIN_NUMBER = GPIO_PIN1 ;
	PinCfg.GPIO_PIN_MODE = GPIO_OUTPUT_PP ;
	PinCfg.GPIO_OUT_SPEED = GPIO_OUT_SPEED_10MHZ;
	MCAL_GPIO_Init(GPIOB, &PinCfg);


}
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
	HAL_LCD_GoToXY(LCD_ROW1, LCD_Column1);
	HAL_LCD_Display_String("IRQ EXTI9");
	HAL_LCD_GoToXY(LCD_ROW2, LCD_Column1);
	HAL_LCD_Display_String("is happened _|-");
	wait(1000);

}
int main()
{
	//ENABLE CLOCK
	CLK_init();
	// LCD INITIALIZATION
	HAL_LCD_Init();
	//EXTI CONFIG
	EXTI_Config_t MyExti ;
	MyExti.EXT_PIN_CONFIG = EXTI9PB9 ;
	MyExti.TRIGGER_CASE = EXTI_RISING_EDGE ;
	MyExti.PTR_CALLBACK_FUN = EXTI9_CallBack ;
	MyExti.IRQ_EN = IRQ_ENABLE ;
	MCAL_EXTI_Init(&MyExti);
	IRQ_Flag = 1 ;

	while(1)
	{

		if(IRQ_Flag)
		{
			HAL_LCD_Clear_Screen();
			IRQ_Flag = 0 ;
		}

		wait(1000);

	}
	return 0 ;
}

