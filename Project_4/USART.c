#include "USART.h"


// USART1 --> 72MHz
// USART2 and USART3 --> 36MHz
// USART2 --> PA2 (TX) and PA3(RX)
// USART1 --> PA9 (TX) and PA10(RX)
// USART2 --> PB10 (TX) and PB11(RX)


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
	dec = frac;
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

void init_USART(unsigned short usart, unsigned long BR)
{
	unsigned long BRR_Cal;
	
	BRR_Cal = USART_BRR(usart,BR);
	// Enable the Alternate Function for PINS
	
	if (usart == 1)
	{
		// ************* Init UART************** //
		
		// Enable UART1
		// Enable the related pins
		// Setup the buad rate for the UART
		// Enable UART transmit(CR)
		// Enable UART receive (CR)
		// Enable UART
		
	}
	else if(usart == 2)
	{
		// Enable UART1
		// Enable the related pins
		// Setup the buad rate for the UART
		// Enable UART transmit(CR)
		// Enable UART receive (CR)
		// Enable UART
		
	}
	else if(usart == 3)
	{
		// Enable UART1
		// Enable the related pins
		// Setup the buad rate for the UART
		// Enable UART transmit(CR)
		// Enable UART receive (CR)
		// Enable UART
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
