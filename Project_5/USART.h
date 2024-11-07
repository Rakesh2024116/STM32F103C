#ifndef USART_H
#define USART_H

#include	"stm32f10x.h"

void init_USART(unsigned short usart, unsigned long BR);
unsigned long USART_BRR(unsigned short usart, unsigned long BR);

char UART_RX(unsigned short uart);
void UART_TX(unsigned short uart, char c);

#endif
