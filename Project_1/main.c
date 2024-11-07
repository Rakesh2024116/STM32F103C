#include "stm32f10x.h"                  // Device header


void delay(int rep);
	
int main(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;	// Enable the APB2 register for accessing the IO port C
	// Method - 1
		GPIOC->CRH &= 0xFF0FFFFF; // Make the bit to 0 of port C pin 13
		GPIOC->CRH |= GPIO_CRH_MODE13; // Set the pin 13 to General purpose output push-pull (ans = 0x44344444)
	
		//GPIOC->ODR |= GPIO_ODR_ODR13; // 0x00002000 (last 4 bits are reserved. only work done on first four bits for 16 pins)
		/*while(1)
		{
			// ODR is both read and write mode register ***In the ODR register the bits from 16 to 31 are reserved***
			GPIOC->ODR |= GPIO_ODR_ODR13; // (GPIO_ODR_ODR13 = 0x2000) setting the pin 13 bit
			delay(10);
			GPIOC->ODR &= ~GPIO_ODR_ODR13; // (~GPIO_ODR_ODR13 = 0xDFFF) reseting the pin 13 bit
			delay(10);
		}*/
	
	/*Method - 2*/
	//GPIOC->CRH &= 0xFF3FFFFF; // Set the pin 13 to General purpose output push-pull(0xFF3FFFFF)
	// BLINK
	while(1)
	{
		// BSRR is only write mode register
		GPIOC->BSRR |= GPIO_BSRR_BS13; // (GPIO_BSRR_BS13=0x00002000) setting the pin 13 bit
		delay(10);
		GPIOC->BSRR = GPIO_BSRR_BR13; // (GPIO_BSRR_BR13=0x20000000) reseting the pin 13 bit
		delay(10);
	}
}                      
/*Custom delay function*/
void delay(int rep)
{
	for (;rep>0;rep--)
	{
		for(int i = 0; i<100000; i++)
		{}
	}
}
