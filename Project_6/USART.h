#ifndef USART_H
#define USART_H
#include <stm32f10x.h>
#include "gpio_driver.h"

unsigned long USART_BRR(unsigned short usart, unsigned long BR);
void init_USART(unsigned short usart, unsigned long BR);


char UART_RX(unsigned short uart);
void UART_TX(unsigned short uart, char c);

#define Txdre 0x0080

#define Rxdre	0x0000

#endif
