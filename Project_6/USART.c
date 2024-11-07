#include "USART.h"


unsigned long USART_BRR(unsigned short usart, unsigned long BR)
{
	unsigned long dec;
	unsigned long final;
	unsigned long div =  36000000UL;
	double frac = 36000000.00;
	double frac2 = 1.00;
	
	if (usart ==1)
	{
		unsigned long div =  72000000UL; // (clock speed)
		double frac = 72000000.00;
	}
	
	div = div / (BR*16);
	frac = 16*((frac / (BR*16))-div);
	dec = (unsigned long)(frac);
	frac2 = 100*(frac-dec);
	if(frac2>50)
	{
		dec++;
		if (dec == 16)
		{
			dec = 0;
			div++;
		}
	}
	final = (div<<4);
	final += dec;
	return final;
	
}

// Frequency 
// USART1 --> 72MHz
// USART2 and USART3 --> 36MHz

// USART1 --> PA9 (TX) and PA10(RX)
// USART2 --> PA2 (TX) and PA3(RX)
// USART2 --> PB10 (TX) and PB11(RX)

void init_USART(unsigned short usart, unsigned long BR)
{
	unsigned long BRR_Cal;
	
	// Baud Rate Calculation  
	BRR_Cal = USART_BRR(usart,BR);
	
	// Enable the Alternate Function for PINS
	RCC->APB2ENR |= 0x00000001;
	
	// Select according to the parameter 
	if (usart == 1)
	{
		// ************* Init UART************** //
		
		// Enable UART1
		RCC->APB2ENR |= 0x00004000; // 14th bit set for the USART1 Enable
		// Enable the related pins(Tx and Rx)
		init_GPIO(POA, 9, OUT50, OP_AF_PP); // Port A pin 9 as Transmitter
		init_GPIO(POA, 10, IN, IN_PP);	// Port A pin 10 as Receiver
		// Setup the buad rate for the UART
		USART1->BRR = (unsigned short)(BRR_Cal);
		// Enable UART transmit(CR1)
		USART1->CR1 |= 0x0008;	// 3rd bit set to 1
		// Enable UART receive (CR1)
		USART1->CR1 |= 0x0004;	// 2nd bit set to 1
		// Enable UART
		USART1->CR1 |= 0x2000;	// 13th bit set to 1
		
	}
	else if(usart == 2)
	{
		// Enable UART2
		RCC->APB1ENR |= 0x00020000; // 17th bit set to 1 
		// Enable the related pins(Tx and Rx)
		init_GPIO(POA, 2, OUT50, OP_AF_PP); // Port A pin 2 as Transmitter
		init_GPIO(POA, 3, IN, IN_PP);	// Port A pin 3 as Receiver
		// Setup the buad rate for the UART
		USART2->BRR = (unsigned short)(BRR_Cal);
		// Enable UART transmit(CR1)
		USART2->CR1 |= 0x0008;	// 3rd bit set to 1
		// Enable UART receive (CR1)
		USART2->CR1 |= 0x0004;	// 2nd bit set to 1
		// Enable UART
		USART2->CR1 |= 0x2000;	// 13th bit set to 1
		
	}
	else if(usart == 3)
	{
		// Enable UART3
		RCC->APB1ENR |= 0x00040000;
		// Enable the related pins
		init_GPIO(POB, 10, OUT50, OP_AF_PP);
		init_GPIO(POB, 11, IN, IN_PP);
		// Setup the buad rate for the UART
		USART3->BRR = (unsigned short)(BRR_Cal);
		// Enable UART transmit(CR)
		USART3->CR1 |= 0x0008;
		// Enable UART receive (CR)
		USART3->CR1 |= 0x0004;
		// Enable UART
		USART3->CR1 = 0x2000;
	}
}

char UART_RX(unsigned short uart)
{
	char c;
	if(uart == 1)
	{
		while((USART1->SR & 0x20) == 0x00)
		{}
		c = (char)(USART1->DR);
	}
	else if(uart == 2)
	{
		while((USART2->SR & 0x20) == 0x00)
		{}
		c = (char)(USART2->DR);
	}
	else if(uart == 3)
	{
		while((USART3->SR & 0x20) == 0x00)
		{}
		c = (char)(USART3->DR);	
	}
	return c;
}

void UART_TX(unsigned short uart, char c)
{
	if(uart == 1)
	{
		while((USART1->SR & (1<<6)) == 0x00)
		{}
		USART1->DR = c;
	}
	else if(uart == 2)
	{
		while((USART2->SR & (1<<6))  == 0x00)
		{}
		USART2->DR = c;
	}
	else if(uart == 3)
	{
		while((USART3->SR & (1<<6))  == 0x00)
		{}
		USART3->DR = c;	
	}
}