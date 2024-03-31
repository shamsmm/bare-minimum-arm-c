#include "gpio.h"
#include "rcc.h"
#include "bluepill.h"

#define DELAY_DURATION 150000

// duration is in number of nop instructions, not time
void delay() {
    for (unsigned int i = 0; i < DELAY_DURATION; ++i) __asm__ volatile ("nop");
}

void main() {
    clockConfiguration(BLUEPILL_GPIO_CLOCK);
    pinMode(PC13, OUTPUT);
    pinMode(PB9, INPUT_PULLUP);

    while(1) {
        // Turn on LED on
        digitalWrite(PC13, !digitalRead(PB9));
    }
}