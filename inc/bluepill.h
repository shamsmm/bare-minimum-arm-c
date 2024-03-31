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

const static struct GPIO_CONFIGURATION INPUT = {GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOATING};
const static struct GPIO_CONFIGURATION INPUT_PULLUP = {GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULLED_UP_OR_DOWN, HIGH};
const static struct GPIO_CONFIGURATION INPUT_PULLDOWN = {GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULLED_UP_OR_DOWN, LOW};

const static struct GPIO PC13 = {PORTC,13};
const static struct GPIO PC14 = {PORTC,14};
const static struct GPIO PC15 = {PORTC,15};

const static struct GPIO PA0 = {PORTA, 0};
const static struct GPIO PA1 = {PORTA, 1};
const static struct GPIO PA2 = {PORTA, 2};
const static struct GPIO PA3 = {PORTA, 3};
const static struct GPIO PA4 = {PORTA, 4};
const static struct GPIO PA5 = {PORTA, 5};
const static struct GPIO PA6 = {PORTA, 6};
const static struct GPIO PA7 = {PORTA, 7};

const static struct GPIO PB0 = {PORTB, 0};
const static struct GPIO PB1 = {PORTB, 1};
const static struct GPIO PB2 = {PORTB, 2};
const static struct GPIO PB3 = {PORTB, 3};
const static struct GPIO PB4 = {PORTB, 4};
const static struct GPIO PB5 = {PORTB, 5};
const static struct GPIO PB6 = {PORTB, 6};
const static struct GPIO PB7 = {PORTB, 7};
const static struct GPIO PB8 = {PORTB, 8};
const static struct GPIO PB9 = {PORTB, 9};

const static struct ClockConfiguration BLUEPILL_GPIO_CLOCK = {RCC_APB2ENR, IOPA | IOPB | IOPC};




#endif //C0_BLUEPILL_H
