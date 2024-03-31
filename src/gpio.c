#include "gpio.h"

void pinMode(const struct GPIO gpio, struct GPIO_CONFIGURATION conf) {
    if (gpio.pin < 8) {
        *(gpio.port + GPIOx_CRL) &= ~(0x1111 << (gpio.pin * 4));
        *(gpio.port + GPIOx_CRL) |= (((conf.mode & 0x11) | (conf.cnf & 0x11) << 2) << (gpio.pin * 4));
    } else {
        *(gpio.port + GPIOx_CRH) &= ~(0x1111 << ((gpio.pin - 8) * 4));
        *(gpio.port + GPIOx_CRH) |= ((conf.mode & 0x11) | (conf.cnf & 0x11) << 2) << ((gpio.pin - 8) * 4);
    }
}

void digitalWrite(struct GPIO gpio, enum GPIO_STATE state) {
    *(gpio.port + GPIOx_ODR) = (state != 0) << gpio.pin;
}

enum GPIO_STATE digitalRead(struct GPIO gpio) {
    return (*(gpio.port + GPIOx_IDR) & (1 << gpio.pin)) != 0 ? HIGH : LOW;
}

void digitalSet(struct GPIO gpio) {
    *(gpio.port + GPIOx_BSRR) = 1 << gpio.pin;
}

void digitalReset(struct GPIO gpio) {
    *(gpio.port + GPIOx_BSRR) = 1 << gpio.pin << 16;
}



