#include <stm32f10x.h>
#include "systick_timer.h"
#include "gpio_driver.h"
#include "USART.h"

int main(void)
{
	systick_init();
	init_USART(2, 256000);
	
	char data = 'R';
	
	while(1)
	{
		// Transmit char
		// 1 - wait untill transmitter data register is empty
		while(!(USART2->SR & Txdre)){}
		// 2 - assaign the value to the data register 
		USART2->DR = data;
		
		// Receive char
	}
}

