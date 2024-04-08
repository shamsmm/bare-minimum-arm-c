#include "gpio.h"
#include "rcc.h"
#include "bluepill.h"
#include "adc.h"

#define DELAY_DURATION 150000

// duration is in number of nop instructions, not time
void delay() {
    for (unsigned int i = 0; i < DELAY_DURATION; ++i) __asm__ volatile ("nop");
}

unsigned short int value;

void main() {
    enablePLLAsSystemClock(PLL_Speed_128Mhz);
    enableClocks(BLUEPILL_ALL_APB2_INTERFACES_CLOCK);
    enableUART(USART1, PLL_Speed_128Mhz / 2, 9600);

    pinMode(PA9, ALTERNATE_PUSH_PULL);
    pinMode(PA8, ALTERNATE_PUSH_PULL);
    pinMode(PC13, OUTPUT_ULTRA_FAST);


    while(1) {
        UART_Transmit(USART1, 'a');
        delay();
        digitalWrite(PC13, HIGH);
        delay();
        digitalWrite(PC13, LOW);
    }
}