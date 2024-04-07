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
    pinModeByte(PB0PB7, OUTPUT);
    pinModeByte(PB8PB15, INPUT_PULLDOWN);

    while(1) {
        // Turn on LED on
        digitalWrite(PC13, !digitalReadByte(PB8PB15));
        digitalWriteByte(PB0PB7, !digitalRead(PB11) << 6);
    }
}