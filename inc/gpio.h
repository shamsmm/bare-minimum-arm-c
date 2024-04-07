#ifndef C0_GPIO_H
#define C0_GPIO_H

#include "common.h"

#define GPIOx_CRL 0
#define GPIOx_CRH 1
#define GPIOx_IDR 2
#define GPIOx_ODR 3
#define GPIOx_BSRR 4

#define GPIO_MODE_INPUT 0
#define GPIO_MODE_OUTPUT_10MHz 1
#define GPIO_MODE_OUTPUT_2MHz 2
#define GPIO_MODE_OUTPUT_50MHz 3

#define GPIO_CNF_INPUT_ANALOG 0
#define GPIO_CNF_INPUT_FLOATING 1
#define GPIO_CNF_INPUT_PULLED_UP_OR_DOWN 2

#define GPIO_CNF_OUTPUT_PUSH_PULL 0
#define GPIO_CNF_OUTPUT_OPEN_DRAIN 1
#define GPIO_CNF_OUTPUT_ALTERNATE_PUSH_PULL 2
#define GPIO_CNF_OUTPUT_ALTERNATE_OPEN_DRAIN 3

typedef enum GPIO_STATE {
    HIGH = 1,
    LOW = 0,
} GPIO_STATE;

typedef struct GPIO {
    volatile unsigned long * port;
    byte pin;
    byte adc;
} GPIO;

typedef struct GPIOBYTE {
    volatile unsigned long * port;
    byte offset;
} GPIOBYTE;

typedef struct GPIOHALFWORD {
    volatile unsigned long * port;
} GPIOHALFWORD;


typedef struct GPIO_CONFIGURATION {
    byte mode;
    byte cnf;
    GPIO_STATE odr;
} GPIO_CONFIGURATION;

void digitalWrite(GPIO gpio, GPIO_STATE state);

void digitalWriteByte(GPIOBYTE gpiobyte, byte data);

void digitalWriteHalfWord(GPIOHALFWORD gpiobyte, unsigned short data);

GPIO_STATE digitalRead(GPIO gpio);

byte digitalReadByte(GPIOBYTE gpiobyte);

short digitalReadHalfWord(GPIOHALFWORD gpiohalfword);

void digitalSet(GPIO gpio);

void digitalReset(GPIO gpio);

void pinMode(GPIO, GPIO_CONFIGURATION);

void pinModeByte(GPIOBYTE, GPIO_CONFIGURATION);

void pinModeHalfWord(GPIOHALFWORD, GPIO_CONFIGURATION);


#endif //C0_GPIO_H
