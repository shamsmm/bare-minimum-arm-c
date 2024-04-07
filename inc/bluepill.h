#ifndef C0_BLUEPILL_H
#define C0_BLUEPILL_H

#include "gpio.h"
#include "rcc.h"

#define PORTA (volatile unsigned long *) 0x40010800
#define PORTB (volatile unsigned long *) 0x40010C00
#define PORTC (volatile unsigned long *) 0x40011000

#define ADC1  (volatile unsigned long *) 0x40012400
#define ADC2  (volatile unsigned long *) 0x40012800


const static GPIO_CONFIGURATION OUTPUT = {GPIO_MODE_OUTPUT_2MHz, GPIO_CNF_OUTPUT_PUSH_PULL};
const static GPIO_CONFIGURATION OUTPUT_FAST = {GPIO_MODE_OUTPUT_10MHz, GPIO_CNF_OUTPUT_PUSH_PULL};
const static GPIO_CONFIGURATION OUTPUT_ULTRA_FAST = {GPIO_MODE_OUTPUT_50MHz, GPIO_CNF_OUTPUT_PUSH_PULL};

const static GPIO_CONFIGURATION INPUT = {GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOATING};
const static GPIO_CONFIGURATION INPUT_PULLUP = {GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULLED_UP_OR_DOWN, HIGH};
const static GPIO_CONFIGURATION INPUT_PULLDOWN = {GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULLED_UP_OR_DOWN, LOW};

const static GPIO PC13 = {PORTC,13};
const static GPIO PC14 = {PORTC,14};
const static GPIO PC15 = {PORTC,15};

const static GPIO PA0 = {PORTA, 0};
const static GPIO PA1 = {PORTA, 1};
const static GPIO PA2 = {PORTA, 2};
const static GPIO PA3 = {PORTA, 3};
const static GPIO PA4 = {PORTA, 4};
const static GPIO PA5 = {PORTA, 5};
const static GPIO PA6 = {PORTA, 6};
const static GPIO PA7 = {PORTA, 7};

const static GPIO PB0 = {PORTB, 0};
const static GPIO PB1 = {PORTB, 1};
const static GPIO PB2 = {PORTB, 2};
const static GPIO PB3 = {PORTB, 3};
const static GPIO PB4 = {PORTB, 4};
const static GPIO PB5 = {PORTB, 5};
const static GPIO PB6 = {PORTB, 6};
const static GPIO PB7 = {PORTB, 7};
const static GPIO PB8 = {PORTB, 8};
const static GPIO PB9 = {PORTB, 9};
const static GPIO PB10 = {PORTB, 10};
const static GPIO PB11 = {PORTB, 11};
const static GPIO PB12 = {PORTB, 12};
const static GPIO PB13 = {PORTB, 13};
const static GPIO PB14 = {PORTB, 14};
const static GPIO PB15 = {PORTB, 15};

const static GPIOBYTE PA0PA7 = {PORTA, 0};

const static GPIOBYTE PB0PB7 = {PORTB, 0};
const static GPIOBYTE PB8PB15 = {PORTB, 8};
const static GPIOHALFWORD PB0PB15 = {PORTB};

const static ClockConfiguration BLUEPILL_GPIO_CLOCK = {RCC_APB2ENR, IOPA | IOPB | IOPC};




#endif //C0_BLUEPILL_H
