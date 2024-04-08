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
    enablePLLAsSystemClock();
    enableClocks(BLUEPILL_ALL_APB2_INTERFACES_CLOCK);
    pinMode(PC13, OUTPUT_ULTRA_FAST);

    while(1) {
        delay();
        digitalWrite(PC13, HIGH);
        delay();
        digitalWrite(PC13, LOW);
    }
}