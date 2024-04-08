#include "uart.h"
#include "rcc.h"

#define UE 13
#define TE 3
#define RE 2

void enableUART(UART uart, unsigned int clock, unsigned int baud) {
    unsigned short mantissa = clock / (16 * baud);
    byte div = (byte) ((mantissa - ((long) clock / (16 * baud))) * 16);
    *(uart.interface + USART_BRR) |= mantissa << 3 | div;
    *(uart.interface + USART_CR1) |= 1 << UE | 1 << TE;
}

void UART_Transmit(UART uart, char data) {
    *(uart.interface + USART_DR) = data;
    while(!(*(uart.interface + USART_SR) >> 6 & 1))
        __asm__ volatile("nop");
}