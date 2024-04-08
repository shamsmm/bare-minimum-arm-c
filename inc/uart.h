#ifndef C0_UART_H
#define C0_UART_H

#include "common.h"

#define USART_SR 0
#define USART_DR 1
#define USART_BRR 2
#define USART_CR1 3
#define USART_CR2 4
#define USART_CR3 5

typedef struct UART {
    volatile unsigned long * interface;
} UART;

typedef union BAUD {
    struct {
        unsigned short fraction: 4;
        unsigned short mantissa: 12;
    };
    unsigned short brr: 16;
} BAUD;

void enableUART(UART uart, unsigned int clock, unsigned int baud);
void UART_Transmit(UART uart, char data);

#endif //C0_UART_H
