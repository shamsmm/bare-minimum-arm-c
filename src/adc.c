#include "adc.h"
#include "gpio.h"

#define ADON 1 << 0
#define CONT 1 << 1
#define CAL 1 << 2
#define RSTCAL 1 << 3

void enableContinuousADC(ADC_CONFIGURATION conf) {
    *(conf.interface + ADC_CR2) |= CONT | ADON;

    for (char i = 0; i < 100; i++)
        __asm__ volatile ("nop");

    *(conf.interface + ADC_CR2) |= ADON;

    *(conf.interface + ADC_CR2) |= CAL;

    while (*(conf.interface + ADC_CR2) >> 3 & 1)
        __asm__ volatile("nop");
}

unsigned short analogReadInterface(ADC_CONFIGURATION conf, ANALOG_CHANNEL channel) {
    *(conf.interface + ADC_SQR3) = channel;
    *(conf.interface + ADC_SR) &= ~(0x2);

    while (!(*(conf.interface + ADC_SR) >> 1 & 0x1))
        __asm__ volatile ("nop");

    return *(conf.interface + ADC_DR);
}