/*
 * stm32_f103_x6.h
 *
 *  Created on: Jul 4, 2023
 *      Author: adham
 */

#ifndef INCLUDES_STM32_F103_X6_H_
#define INCLUDES_STM32_F103_X6_H_
//-----------------------------
//Includes
#include "stdlib.h"
#include "std_macros.h"
#include "std_types.h"
//-----------------------------



//-----------------------------
//Base addresses for Memories

#define FLASH_MEMORY_BASE	 		  0x08000000UL
#define SYSTEM_MEMORY_BASE			  0x1FFFF000UL
#define SRAM_MEMORY_BASE			  0x20000000UL

#define PERIPHRALS_BASE		  		  0x40000000UL
#define INT_PERIPHRALS_BASE	  		  0xE0000000UL
//-----------------------------



//-----------------------------
//Base addresses for BUS Peripherals

//@RCC: Reset and Control Circuit base address -> AHB bus
#define RCC_BASE 		0x40021000UL


//@GPIO : General Purpose Input Output base addresses -> APB2 bus
//**************************LQFP48***********************************//

//GPIOA&&GPIOB -> ARE FULLY INCLUDED
#define GPIOA_BASE 		0x40010800UL
#define GPIOB_BASE 		0x40010C00UL

//GPIOC&&GPIOD -> ARE PARTIAL INCLUDED
#define GPIOC_BASE 		0x40011000UL
#define GPIOD_BASE 		0x40011400UL

//GPIOE IS NOT INCULDED
#define GPIOE_BASE 		0x40011800UL


//@AFIO: Alternative Functions Input Output Base addresses -> APB2 bus
#define AFIO_BASE 		0x40010000UL

//@EXTI : External Interrupt peripheral base address -> APB2 bus
#define EXTI_BASE 		0x40010400UL

//-----------------------------


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:

//@RCC peripheral REGISTERS
typedef struct
{
	volatile uint32_t RCC_CR 		; // CR : Clock Control Register
	volatile uint32_t RCC_CFGR 		; // CFGR : CLOCK CONFIGURATION REGISTER
	volatile uint32_t RCC_CIR		; // CIR : CLOCK INTERRUPT REGISTER
	volatile uint32_t RCC_APB2RSTR	; // APB2RSTR : APB2 RESET REGISTER
	volatile uint32_t RCC_APB1RSTR	; // APB1RSTR : APB1 RESET REGISTER
	volatile uint32_t RCC_AHBENR	; // AHBENR : AHB CLOCK ENABLE REGISTER
	volatile uint32_t RCC_APB2ENR	; // APB2ENR : APB2 CLOCK ENABLE REGISTER
	volatile uint32_t RCC_APB1ENR	; // APB1ENR : APB1 CLOCK ENABLE REGISTER
	volatile uint32_t RCC_BDCR		; //BDCR : BACKUP DOMAIN CONTROL REGISTER
	volatile uint32_t RCC_CSR		; // CSR : CONTROL / STATUS REGISTER
	volatile uint32_t RCC_AHBSTR		; // AHBSTR : AHB CLOCK RESET REGISTER
}RCC_Registers_t;

//@GPIOx peripheral REGISTERS -> SAME FOR A,B,C,D,E (each port consists of 16 pin)
typedef struct
{
	volatile uint32_t GPIOx_CRL 	; // CRL : GPIO CONTROL REGISTER LOW
	volatile uint32_t GPIOx_CRH 	; // CRH : GPIO CONTROL REGISTER LOW
	volatile uint32_t GPIOx_IDR 	; // IDR : GPIO INPUT DATA REGUSTER
	volatile uint32_t GPIOx_ODR 	; // ODR : GPIO OUTPUT DATA REGISTER
	volatile uint32_t GPIOx_BSRR ; // BSRR : GPIO BIT SET/RESET REGISTER
	volatile uint32_t GPIOx_BRR 	; // BRR : GPIO BIT RESET REGISTER
	volatile uint32_t GPIOx_LCKR ; // LCKR : GPIO LOCK REGISTER
}GPIOx_Registers_t;


//@AFIO peripheral registers
typedef struct
{
	volatile uint32_t AFIO_EVCR 	; //EVCR : EVENT CONTROL REGISTER
	volatile uint32_t AFIO_MAPR 	; //MAPR : REMAP AND DEBUG I/O CONFIGURATION REGSITER
	volatile uint32_t ADIO_EXTICR1 	; //EXTICR1 : EXTERNAL INTERRUPT CONFIGURATION REGISTER 1
	volatile uint32_t ADIO_EXTICR2 	; //EXTICR2 : EXTERNAL INTERRUPT CONFIGURATION REGISTER 2
	volatile uint32_t ADIO_EXTICR3 	; //EXTICR3 : EXTERNAL INTERRUPT CONFIGURATION REGISTER 3
	volatile uint32_t ADIO_EXTICR4 	; //EXTICR4 : EXTERNAL INTERRUPT CONFIGURATION REGISTER 4
	volatile uint32_t reserved 		;
	volatile uint32_t AFIO_MAPR2 	; //MAPR2 : REMAP AND DEBUG I/O CONFIGURATION REGSITER 2
}AFIO_Registers_t;


//@EXTI Peripheral Registers
typedef struct
{
	volatile uint32_t EXTI_IMR 		; //IMR : INTERRUPT MASK REGISTER
	volatile uint32_t EXTI_EMR 		; //EMR : EVENT MASK REGISTER
	volatile uint32_t EXTI_RTSR 	; //RTSR : RISING TRIGGER SELECTION REGISTER
	volatile uint32_t EXTI_FTSR 	; //FTSR : FALLING TRIGGER SELECTION REGISTER
	volatile uint32_t EXTI_SWIER	; //SWIER : SOFTWARE INTERRUPT EVENT REGISTER
	volatile uint32_t EXTI_PR		; //PR : PENDING REGISTER
}EXTI_Registers_t;

//-*-*-*-*-*-*-*-*-*-*-*


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//@GPIO Peripheral instants
#define GPIOA	((volatile GPIOx_Registers_t *)GPIOA_BASE )
#define GPIOB	((volatile GPIOx_Registers_t *)GPIOB_BASE )
#define GPIOC	((volatile GPIOx_Registers_t *)GPIOC_BASE )
#define GPIOD	((volatile GPIOx_Registers_t *)GPIOD_BASE )
#define GPIOE	((volatile GPIOx_Registers_t *)GPIOE_BASE )

//@RCC Peripheral instants
#define RCC	   ((volatile RCC_Registers_t *)RCC_BASE )

//@AFIO Peripheral instants
#define AFIO	((volatile AFIO_Registers_t *)AFIO_BASE )

//@EXTI Peripheral instants
#define EXTI	((volatile EXTI_Registers_t *)EXTI_BASE )

//-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:

//@GPIOA : ENABLE
#define RCC_GPIOA_CLK_EN()	(RCC->RCC_APB2ENR |= 1<<2)
#define RCC_GPIOB_CLK_EN()	(RCC->RCC_APB2ENR |= 1<<3)
#define RCC_GPIOC_CLK_EN()	(RCC->RCC_APB2ENR |= 1<<4)
#define RCC_GPIOD_CLK_EN()	(RCC->RCC_APB2ENR |= 1<<5)
#define RCC_GPIOE_CLK_EN()	(RCC->RCC_APB2ENR |= 1<<6)

//@AFIO : ENABLE
#define RCC_AFIO_CLK_EN()	(RCC->RCC_APB2ENR |= 1<<0)
//-*-*-*-*-*-*-*-*-*-*-*

#endif /* INCLUDES_STM32_F103_X6_H_ */
