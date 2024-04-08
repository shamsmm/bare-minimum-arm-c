#ifndef C0_BLUEPILL_H
#define C0_BLUEPILL_H

#include "gpio.h"
#include "rcc.h"
#include "adc.h"
#include "uart.h"

#define PORTA (volatile unsigned long *) 0x40010800
#define PORTB (volatile unsigned long *) 0x40010C00
#define PORTC (volatile unsigned long *) 0x40011000

typedef enum ClockSpeed {
    PLL_Speed_72Mhz,
    PLL_Speed_128Mhz,
} ClockSpeed;

const static ADC_CONFIGURATION ADC1 = {(volatile unsigned long *) 0x40012400};

const static UART USART1 = {(volatile unsigned long *) 0x40013800};
const static BAUD BAUD_9600 = {12, 285};
//const static BAUD BAUD_9600 = {12, 285};

const static GPIO_CONFIGURATION OUTPUT = {GPIO_MODE_OUTPUT_2MHz, GPIO_CNF_OUTPUT_PUSH_PULL};
const static GPIO_CONFIGURATION OUTPUT_FAST = {GPIO_MODE_OUTPUT_10MHz, GPIO_CNF_OUTPUT_PUSH_PULL};
const static GPIO_CONFIGURATION OUTPUT_ULTRA_FAST = {GPIO_MODE_OUTPUT_50MHz, GPIO_CNF_OUTPUT_PUSH_PULL};
const static GPIO_CONFIGURATION ALTERNATE_PUSH_PULL = {GPIO_MODE_OUTPUT_50MHz, GPIO_CNF_OUTPUT_ALTERNATE_PUSH_PULL};

const static GPIO_CONFIGURATION INPUT = {GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOATING};
const static GPIO_CONFIGURATION ANALOG_INPUT = {GPIO_MODE_INPUT, GPIO_CNF_INPUT_ANALOG};
const static GPIO_CONFIGURATION INPUT_PULLUP = {GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULLED_UP_OR_DOWN, HIGH};
const static GPIO_CONFIGURATION INPUT_PULLDOWN = {GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULLED_UP_OR_DOWN, LOW};

const static GPIO PC13 = {PORTC,13, NC};
const static GPIO PC14 = {PORTC,14, NC};
const static GPIO PC15 = {PORTC,15, NC};

const static GPIO PA0 = {PORTA, 0, CHANNEL0};
const static GPIO PA1 = {PORTA, 1, CHANNEL1};
const static GPIO PA2 = {PORTA, 2, CHANNEL2};
const static GPIO PA3 = {PORTA, 3, CHANNEL3};
const static GPIO PA4 = {PORTA, 4, CHANNEL4};
const static GPIO PA5 = {PORTA, 5, CHANNEL5};
const static GPIO PA6 = {PORTA, 6, CHANNEL6};
const static GPIO PA7 = {PORTA, 7, CHANNEL7};
const static GPIO PA8 = {PORTA, 8, NC};
const static GPIO PA9 = {PORTA, 9, NC};

const static GPIO PB0 = {PORTB, 0, CHANNEL8};
const static GPIO PB1 = {PORTB, 1, CHANNEL9};
const static GPIO PB2 = {PORTB, 2, NC};
const static GPIO PB3 = {PORTB, 3, NC};
const static GPIO PB4 = {PORTB, 4, NC};
const static GPIO PB5 = {PORTB, 5, NC};
const static GPIO PB6 = {PORTB, 6, NC};
const static GPIO PB7 = {PORTB, 7, NC};
const static GPIO PB8 = {PORTB, 8, NC};
const static GPIO PB9 = {PORTB, 9, NC};
const static GPIO PB10 = {PORTB, 10, NC};
const static GPIO PB11 = {PORTB, 11, NC};
const static GPIO PB12 = {PORTB, 12, NC};
const static GPIO PB13 = {PORTB, 13, NC};
const static GPIO PB14 = {PORTB, 14, NC};
const static GPIO PB15 = {PORTB, 15, NC};

const static GPIOBYTE PA0PA7 = {PORTA, 0};

const static GPIOBYTE PB0PB7 = {PORTB, 0};
const static GPIOBYTE PB8PB15 = {PORTB, 8};
const static GPIOHALFWORD PB0PB15 = {PORTB};

const static ClockConfiguration BLUEPILL_ALL_APB2_INTERFACES_CLOCK = {RCC_APB2ENR, IOPAEN | IOPBEN | IOPCEN | ADC1EN | ADC2EN | USART1EN};

unsigned short analogRead(GPIO gpio);

void enablePLLAsSystemClock72MHz();

void enablePLLAsSystemClock128MHz();

#endif //C0_BLUEPILL_H
