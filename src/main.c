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
    enableClocks(BLUEPILL_ALL_APB2_INTERFACES_CLOCK);
    enableContinuousADC(ADC1);

    pinMode(PA1, ANALOG_INPUT);
    pinMode(PC13, OUTPUT_ULTRA_FAST);

    while(1) {
        value = analogRead(PA1);
        if (value > 2000)
            digitalWrite(PC13, LOW);
        else
            digitalWrite(PC13, HIGH);
    }
}