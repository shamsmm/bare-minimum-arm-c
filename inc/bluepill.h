#ifndef C0_BLUEPILL_H
#define C0_BLUEPILL_H

#include "gpio.h"
#include "rcc.h"

#define PORTA (volatile unsigned long *) 0x40010800
#define PORTB (volatile unsigned long *) 0x40010C00
#define PORTC (volatile unsigned long *) 0x40011000


const static struct GPIO_CONFIGURATION OUTPUT = {GPIO_MODE_OUTPUT_2MHz, GPIO_CNF_OUTPUT_PUSH_PULL};
const static struct GPIO_CONFIGURATION OUTPUT_FAST = {GPIO_MODE_OUTPUT_10MHz, GPIO_CNF_OUTPUT_PUSH_PULL};
const static struct GPIO_CONFIGURATION OUTPUT_ULTRA_FAST = {GPIO_MODE_OUTPUT_50MHz, GPIO_CNF_OUTPUT_PUSH_PULL};

const static struct GPIO PC13 = {PORTC,13};
const static struct GPIO PC14 = {PORTC,14};
const static struct GPIO PC15 = {PORTC,15};

const static struct GPIO PA0 = {PORTA, 0};
const static struct GPIO PA1 = {PORTA, 0};
const static struct GPIO PA2 = {PORTA, 0};
const static struct GPIO PA3 = {PORTA, 0};
const static struct GPIO PA4 = {PORTA, 0};
const static struct GPIO PA5 = {PORTA, 0};
const static struct GPIO PA6 = {PORTA, 0};
const static struct GPIO PA7 = {PORTA, 0};

const static struct GPIO PB0 = {PORTB, 0};

const static struct ClockConfiguration BLUEPILL_GPIO_CLOCK = {RCC_APB2ENR, IOPA | IOPB | IOPC};




#endif //C0_BLUEPILL_H
