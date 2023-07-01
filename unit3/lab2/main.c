/*embedded c Code of ARM-CORTEX-M3 TO TOGGLE A LED CONNECTED TO PA13 */
#include <stdint.h>
typedef volatile unsigned int vuint32_t ;
//define addresses 
#define RCC_BASE 0x40021000
#define GPIO_BASE 0x40010800
#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE+0x18)
#define GPIO_CRH *(volatile uint32_t *)(GPIO_BASE+0x04)
#define GPIO_ODR *(volatile uint32_t *)(GPIO_BASE+0x0C)
//bit field 
#define RCC_IOPAEN (1<<2)
#define GPIOA13 (1UL<<13)
typedef union {
	vuint32_t all_bits ; 
	struct {
		vuint32_t reserved :13 ; 
		vuint32_t p_13 :1 ;
	}pin;
}R_ODR_T;
volatile R_ODR_T* R_ODR = (volatile R_ODR_T *)(GPIO_BASE+0x0C); // POINTER TO ODR REGISTER 
//unsigned char g-var[3]={1,2,3}; // golbal initilaized variable to create .data section 
//unsigned const char cons-var[3]={1,2,3}; // constant variable to creat .rodata section 
int main(void)
{
	RCC_APB2ENR = RCC_IOPAEN ; // TO ENABLE CLOCK SIGNAL FOR GPIOA 
	GPIO_CRH &= 0xFF0FFFFF ; 
	GPIO_CRH |= 0x00200000 ;
	while(1)
	{
		R_ODR->pin.p_13 = 1 ; 
		for(int i = 0 ; i<5000 ; i++); //delay 
		R_ODR->pin.p_13 =  0 ; 
		for(int i = 0 ; i<5000 ; i++); //delay
		
	}
	//end of embedded c code 
	
}

