/*
 * main.c
 *
 *  Created on: Jul 1, 2023
 *      Author: adham
 */
#include<stdint.h>

// define the RCC registers
#define RCC_BASE 0x40021000
#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE + 0x18)

void rcc_clock_init()
{
	RCC_APB2ENR |= 1<<2 ; // enable IOPA
	RCC_APB2ENR |= 1<<3 ; // enable IOPB
}

// define the GPIO registers
#define GPIOA_BASE 0x40010800
#define GPIOB_BASE (0x40010C00)

#define GPIOA_CRL *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_IDR *(volatile uint32_t *)(GPIOA_BASE + 0X08)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0X0C)

#define GPIOB_CRL *(volatile uint32_t *)(GPIOB_BASE + 0x00)
#define GPIOB_CRH *(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_IDR *(volatile uint32_t *)(GPIOB_BASE + 0X08)
#define GPIOB_ODR *(volatile uint32_t *)(GPIOB_BASE + 0X0C)

void GPIO_init()
{
	GPIOA_CRL = 0 ;
	GPIOA_CRH = 0 ;
	GPIOA_ODR = 0 ;
	GPIOA_CRL &= ~( 0b11 <<4 );
	GPIOA_CRL |= (0b01<<6);
	GPIOB_CRL |= (0b01<<4);
	GPIOB_CRL &= ~(0b11<<6);
	GPIOA_CRH &= ~(0b11<<20);
	GPIOA_CRH |= (0b01<<22);
	GPIOB_CRH |= (0b11<<20);
	GPIOB_CRH &=  ~(0b01<<22);
}
void wait_ms(int x)
{
	int i , j ;
	for(i=0 ; i<x ; i++)
		for(j=0 ; j<255 ; j++);
}

int main()
{
	rcc_clock_init();
	GPIO_init();

	while(1)
	{
		if((GPIOA_IDR&(1<<1))>>1 == 0)
		{
			GPIOB_ODR ^= 1<<1 ;
			while((GPIOA_IDR&(1<<1))>>1 == 0);

		}
		if((GPIOA_IDR&(1<<13))>>13 == 1)
		{

			GPIOB_ODR ^= 1<<13 ;
		}
		wait_ms(1);

	}
	return 0 ;
}
