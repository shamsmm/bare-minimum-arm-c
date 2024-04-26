#include "gpio.h"
#include "rcc.h"
#include "bluepill.h"
#include "adc.h"
#include "i2c.h"



// duration is in number of nop instructions, not time
void delay(int duration) {
    for (unsigned int i = 0; i < duration; ++i) __asm__ volatile ("nop");
}

unsigned short int value;

void main() {
    enablePLLAsSystemClock(PLL_Speed_128Mhz);
    enableClocks(BLUEPILL_ALL_APB2_INTERFACES_CLOCK);
    enableClocks(BLUEPILL_ALL_APB1_INTERFACES_CLOCK);

    pinMode(PB6, ALTERNATE_OPEN_DRAIN);
    pinMode(PB7, ALTERNATE_OPEN_DRAIN);

    pinMode(PC13, OUTPUT_ULTRA_FAST);

    I2C_Init();

    while(1) {
        I2C_Send(0x3C, 0xFF);

        delay(200000);
        digitalWrite(PC13, HIGH);
        delay(200000);
        digitalWrite(PC13, LOW);
    }
}