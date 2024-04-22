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
    enableClocks(BLUEPILL_ALL_APB1_INTERFACES_CLOCK);
    enableContinuousADC(ADC1);
    enableUART(USART1, PLL_Speed_128Mhz / 2, 9600);

    pinMode(PA9, ALTERNATE_PUSH_PULL);
    pinMode(PC13, OUTPUT_ULTRA_FAST);

    *TIM2 = 1;
    *(TIM2 + 10) = 10000;

    while(1) {
        unsigned short temp_reading = analogReadInterface(ADC1, CHANNEL16);
        double voltage = (temp_reading / 4095.0) * 3.3;
        unsigned short temp = (unsigned short) ((1.43 - voltage) / 0.0043) + 25;
        UART_Transmit_Number(USART1, *(TIM2 + 9));

        UART_Transmit(USART1, '\r');
        UART_Transmit(USART1, '\n');
        delay();
        digitalWrite(PC13, HIGH);
        delay();
        digitalWrite(PC13, LOW);
    }
}