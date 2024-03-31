#ifndef C0_GPIO_H
#define C0_GPIO_H

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

enum GPIO_STATE {
    HIGH = 1,
    LOW = 0,
};

struct GPIO {
    volatile unsigned long * port;
    char pin;
};

struct GPIO_CONFIGURATION {
    char mode;
    char cnf;
    enum GPIO_STATE odr;
};

void digitalWrite(struct GPIO gpio, enum GPIO_STATE state);
enum GPIO_STATE digitalRead(struct GPIO gpio);
void digitalSet(struct GPIO gpio);
void digitalReset(struct GPIO gpio);
void pinMode(struct GPIO, struct GPIO_CONFIGURATION);


#endif //C0_GPIO_H
