#include "gpio.h"

void pinMode(const struct GPIO gpio, struct GPIO_CONFIGURATION conf) {
    if (gpio.pin < 8) {
        *(gpio.port + GPIOx_CRL) &= ~(0b1111 << (gpio.pin * 4));
        *(gpio.port + GPIOx_CRL) |= (((conf.mode & 0b11) | (conf.cnf & 0b11) << 2) << (gpio.pin * 4));
    } else {
        *(gpio.port + GPIOx_CRH) &= ~(0b1111 << ((gpio.pin - 8) * 4));
        *(gpio.port + GPIOx_CRH) |= ((conf.mode & 0b11) | (conf.cnf & 0b11) << 2) << ((gpio.pin - 8) * 4);
    }

    if (conf.mode == GPIO_MODE_INPUT && conf.cnf == GPIO_CNF_INPUT_PULLED_UP_OR_DOWN)
        digitalWrite(gpio, conf.odr);
}

void pinModeByte(GPIOBYTE gpiobyte, struct GPIO_CONFIGURATION conf) {
    uint8_t pattern = ((conf.mode & 0b11) | (conf.cnf & 0b11) << 2);

    if (gpiobyte.offset != 8) {
        *(gpiobyte.port + GPIOx_CRL) &= ~(0xFFFFFFFF);
        *(gpiobyte.port + GPIOx_CRL) |=
                pattern << 0 |
                pattern << 4 |
                pattern << 8 |
                pattern << 12 |
                pattern << 16 |
                pattern << 20 |
                pattern << 24 |
                pattern << 28;
    } else {
        *(gpiobyte.port + GPIOx_CRH) &= ~(0xFFFFFFFF);
        *(gpiobyte.port + GPIOx_CRH) |=
                pattern << 0 |
                pattern << 4 |
                pattern << 8 |
                pattern << 12 |
                pattern << 16 |
                pattern << 20 |
                pattern << 24 |
                pattern << 28;
    }

    if (conf.mode == GPIO_MODE_INPUT && conf.cnf == GPIO_CNF_INPUT_PULLED_UP_OR_DOWN){
        if (conf.odr) {
            digitalWriteByte(gpiobyte, 0xFF);
        } else {
            digitalWriteByte(gpiobyte, 0x00);
        }
    }
}

void pinModeHalfWord(GPIOHALFWORD gpiohalfword, struct GPIO_CONFIGURATION conf) {
    uint8_t pattern = ((conf.mode & 0b11) | (conf.cnf & 0b11) << 2);

    *(gpiohalfword.port + GPIOx_CRL) &= ~(0xFFFFFFFF);
    *(gpiohalfword.port + GPIOx_CRL) |=
            pattern << 0 |
            pattern << 4 |
            pattern << 8 |
            pattern << 12 |
            pattern << 16 |
            pattern << 20 |
            pattern << 24 |
            pattern << 28;

    *(gpiohalfword.port + GPIOx_CRH) &= ~(0xFFFFFFFF);
    *(gpiohalfword.port + GPIOx_CRH) |=
            pattern << 0 |
            pattern << 4 |
            pattern << 8 |
            pattern << 12 |
            pattern << 16 |
            pattern << 20 |
            pattern << 24 |
            pattern << 28;

    if (conf.mode == GPIO_MODE_INPUT && conf.cnf == GPIO_CNF_INPUT_PULLED_UP_OR_DOWN) {
        if (conf.odr) {
            digitalWriteHalfWord(gpiohalfword, 0xFFFF);
        } else {
            digitalWriteHalfWord(gpiohalfword, 0x0000);
        }
    }
}

void digitalWriteHalfWord(GPIOHALFWORD gpiohalfword, unsigned short data) {
    *(gpiohalfword.port + GPIOx_ODR) = data;
}

void digitalWriteByte(GPIOBYTE gpiobyte, uint8_t data) {
    *(gpiobyte.port + GPIOx_ODR) = (*(gpiobyte.port + GPIOx_ODR) & (~(0xFF) << gpiobyte.offset)) | (data << gpiobyte.offset);
}


void digitalWrite(GPIO gpio, GPIO_STATE state) {
//    *(gpio.port + GPIOx_ODR) &= ~(0x1) << gpio.pin;
//    *(gpio.port + GPIOx_ODR) |= (state != 0) << gpio.pin;
    *(gpio.port + GPIOx_ODR) = (*(gpio.port + GPIOx_ODR) & ~(0x1) << gpio.pin) | ((state != 0) << gpio.pin);
}

GPIO_STATE digitalRead(GPIO gpio) {
    return (*(gpio.port + GPIOx_IDR) & (1 << gpio.pin)) != 0 ? HIGH : LOW;
}

uint8_t digitalReadByte(GPIOBYTE gpiobyte) {
    return (uint8_t) ((*(gpiobyte.port + GPIOx_IDR) >> gpiobyte.offset) & (0xFF));
}

short digitalReadHalfWord(GPIOHALFWORD gpiohalfword) {
    return (short) (*(gpiohalfword.port + GPIOx_IDR) & (0xFFFF));
}

void digitalSet(struct GPIO gpio) {
    *(gpio.port + GPIOx_BSRR) = 1 << gpio.pin;
}

void digitalReset(struct GPIO gpio) {
    *(gpio.port + GPIOx_BSRR) = 1 << gpio.pin << 16;
}



