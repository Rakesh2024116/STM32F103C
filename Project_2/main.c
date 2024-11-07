
#include "stm32f10x.h"                  // Device header
#include "gpio_driver.h"

void delay(int rep);
void EXTI0_IRQHandler(void);
void systick_init(void);
void DelayMillis(void);
void DelayMS(unsigned long t);

static int i = 0;

unsigned short signal = 0;

int main(void)
{
	/*
	RCC_APB2ENR |= 0x00000004; // Enabling Port A
	RCC_APB2ENR |= 0x00000010; // Enabling port C
	
	GPIOA->CRL &= 0xFFFFFFF0; // RESETTING THE PIN 0 (CONFIG 0)
	GPIOA->CRL |= GPIO_CRL_CNF0_1; // Setting the pin 0 to Input with pull up/pull down (0x00000008)
	
	GPIOC->CRH &= 0xFF0FFFFF; // RESETTING THE PIN 13 (CONFIG 0)
	GPIOC->CRH |= GPIO_CRH_MODE13;
	*/
	init_GPIO(POA, 0, IN, IN_PP);
	
	
	__disable_irq();
	AFIO->EXTICR[0] = 0x00;
	EXTI->IMR |= 1;
	EXTI->RTSR |= 1;
	NVIC_EnableIRQ(EXTI0_IRQn);
	__enable_irq();
	
	
	
	while(1)
	{
		Write_GP(POA, 12, signal);
			// if(GPIOA->IDR & 0x00000001)		// 0x00000001
		if (signal == 1)
			{
				// BSRR is only write mode register
				// GPIOC->ODR |= GPIO_ODR_ODR13; // Through the odr register enabled the pin 13
				// GPIOC->BSRR |= GPIO_BSRR_BS13; // (GPIO_BSRR_BS13=0x00002000) setting the pin 13 bit
				// delay(10);
				// GPIOC->BSRR = GPIO_BSRR_BR13; // (GPIO_BSRR_BR13=0x20000000) reseting the pin 13 bit
				//  GPIOC->ODR &= ~(GPIO_ODR_ODR13); 
				// delay(10);
				i = 5;  
			}
			else 
			{
				// GPIOC->ODR ^= (GPIO_ODR_ODR13); // Toggle the state of pc13 using XOR operator
				// GPIOC->ODR = 0x00000000; 
				i = 0;
			}
	}
	
} 

/*Custom delay function*/
void delay(int rep)
{
	for (;rep>0;rep--)
	{
		for(int j = 0; j<100000; j++)
		{}
	}
}

void EXTI0_IRQHandler(void)
{
	EXTI->PR |= 1;
	if(signal)
	{
		signal = 0;
	}
	else
	{
		signal = 1;
	}
}

void systick_init(void)
{
	SysTick->CTRL = 0x00000000;	// Reset all bits to 0
	SysTick->LOAD = 0x00FFFFFF;	// Set all bits to the highest value
	SysTick->VAL = 0x00000000;	// Reset all bits to 0
	SysTick->CTRL = 0x00000005;	// Configure the bits to enable systick and set it to processor clock(AHB) through clksource bit
}

void DelayMillis(void)
{
	SysTick->LOAD = 72000 - 1;
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
}

void DelayMS(unsigned long t)
{
	for(;t>0;t--)
	{
		DelayMillis();
	}
}