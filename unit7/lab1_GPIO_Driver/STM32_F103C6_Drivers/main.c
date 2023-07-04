/*
 * main.c
 *
 *  Created on: Jul 4, 2023
 *      Author: adham
 */
#include"includes/stm32_f103_x6.h"
#include "MCAL/GPIO/GPIO.h"
void CLK_init()
{
	// Enable Clock for GPIOA
	RCC_GPIOA_CLK_EN();
	// Enable Clock for GPIOB
	RCC_GPIOB_CLK_EN();
}
void GPIO_init()
{
	GPIO_Pin_Config_t PinCfg ;

	// CONFIGURE PA1 Floating input
	PinCfg.GPIO_PIN_NUMBER = GPIO_PIN1 ;
	PinCfg.GPIO_PIN_MODE = GPIO_INPUT_FLOAT ;
	MCAL_GPIO_Init(GPIOA, &PinCfg);

	//CONFIGURE PB1 as push-pull output
	PinCfg.GPIO_PIN_NUMBER = GPIO_PIN1 ;
	PinCfg.GPIO_PIN_MODE = GPIO_OUTPUT_PP ;
	PinCfg.GPIO_OUT_SPEED = GPIO_OUT_SPEED_10MHZ;
	MCAL_GPIO_Init(GPIOB, &PinCfg);


	// CONFIGURE PA13 Floating input
	PinCfg.GPIO_PIN_NUMBER = GPIO_PIN13 ;
	PinCfg.GPIO_PIN_MODE = GPIO_INPUT_FLOAT ;
	MCAL_GPIO_Init(GPIOA, &PinCfg);

	//CONFIGURE PB13 as push-pull output
	PinCfg.GPIO_PIN_NUMBER = GPIO_PIN13 ;
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
int main()
{
	CLK_init();
	GPIO_init();
	while(1)
	{
		if(MCAL_GPIO_Pin_Read(GPIOA, GPIO_PIN1) == 0)
		{
			MCAL_GPIO_Pin_Toggle(GPIOB, GPIO_PIN1);
			while(MCAL_GPIO_Pin_Read(GPIOA, GPIO_PIN1) == 0);
		}
		if(MCAL_GPIO_Pin_Read(GPIOA, GPIO_PIN13) == 1)
		{
			MCAL_GPIO_Pin_Toggle(GPIOB, GPIO_PIN13);

		}
		wait(1);

	}
	return 0 ;
}

