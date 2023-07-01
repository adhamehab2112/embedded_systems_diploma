#include<stdint.h>
//extern unsigned int _stack_top;
extern int main();

void reset_handler();
void default_handler()
{
	reset_handler();
}
void NMI_hanlder(void) __attribute__((weak,alias("default_handler")));;
void H_fault_hanlder(void) __attribute__((weak,alias("default_handler")));;
void MM_fault_hanlder(void) __attribute__((weak,alias("default_handler")));;
void Bus_fault_hanlder(void) __attribute__((weak,alias("default_handler")));;
void Usage_fault_hanlder(void) __attribute__((weak,alias("default_handler")));;
/*
uint32_t vectors[]__attribute__((section(".vectors"))) =
{
	uint32_t &_stack_top ,
	uint32_t &reset_handler , 
	uint32_t &NMI_hanlder , 
	uint32_t &H_fault_hanlder , 
	uint32_t &MM_fault_hanlder ,
	uint32_t &Bus_fault_hanlder ,
	uint32_t &Usage_fault_hanlder ,
};
*/

/**************** Let's try another way to creat the vectors section and calculate the stack top *****************/
// in the 1st method we get the _stack_top form linker let's try to define it automaticaly in the startup.c 


static volatile unsigned int Stack_top[256]; // -> golbal uninitialized variable == .bss section 
// so we now stored 1024 byte in the .bss section which is our stack size 
// remember that Stack_top -> holding the address of the firist element in the array 
// so we can say that &Stack_top[0] + sizeof(Stack_top) == address top be assigned in sp register 



// now let's try to define the .vectors section as an array of pointers to function 
void (* const Vectors[])()__attribute__((section(".vectors"))) = 
{
	// pointer to function is a data type just as uint32_t so we cast the addresses with it normaly 
	(void(*)()) ((unsigned long)Stack_top + sizeof(Stack_top)) , 
	&reset_handler , 
	&NMI_hanlder , 
	&H_fault_hanlder , 
	&MM_fault_hanlder ,
	&Bus_fault_hanlder ,
	&Usage_fault_hanlder ,
};

extern unsigned int _S_DATA ; // symbols and each symbole hold an address 
extern unsigned int _E_DATA ; 
extern unsigned int _E_TEXT ;
extern unsigned int _S_BSS ; 
extern unsigned int _E_BSS ; 

void reset_handler()
{
	// copy data from flash to sram 
	unsigned int DATA_SIZE = (unsigned char*) &_E_DATA - (unsigned char*) &_S_DATA ;
	unsigned char *P_src = (unsigned char*) &_E_TEXT ; 
	unsigned char *P_dst = (unsigned char*) &_S_DATA ;
	// start copying .data section 
	for(int i = 0 ; i< DATA_SIZE ; i++)
	{
		*((unsigned char *)P_dst++) = *((unsigned char *)P_src++); 
	}
	// INITIALIZE .bss Section in sram 
	unsigned int BSS_SIZE = (unsigned char*) &_E_BSS - (unsigned char*) &_S_BSS ; 
	*P_dst = (unsigned char*) &_S_BSS ;
	for(int i = 0 ; i< BSS_SIZE ; i++)
	{
		*((unsigned char *)P_dst++) = (unsigned char)0 ; 
	}
	
	// jumping to main function 
	main();
}