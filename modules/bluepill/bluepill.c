#include "bluepill.h"

unsigned short analogRead(GPIO gpio) {
    return gpio.adc == NC ? 0 : analogReadInterface(ADC1, gpio.adc);
}

void enablePLLAsSystemClock72MHz() {
    enablePLLAsSystemClockWithMultiplication(9);
}

void enablePLLAsSystemClock128MHz() {
    enablePLLAsSystemClockWithMultiplication(16);
}

void enablePLLAsSystemClock(ClockSpeed speed) {
    if (speed == PLL_Speed_128Mhz)
        enablePLLAsSystemClockWithMultiplication(16);
    else if (speed == PLL_Speed_72Mhz)
        enablePLLAsSystemClockWithMultiplication(9);
}