#ifndef C0_RCC_H
#define C0_RCC_H

#define RCC (volatile unsigned long *) 0x40021000

#define RCC_APB2ENR 6

#define IOPAEN 1 << 2
#define IOPBEN 1 << 3
#define IOPCEN 1 << 4
#define ADC1EN 1 << 9
#define ADC2EN 1 << 10

typedef struct ClockConfiguration {
    char offset;
    short value;
} ClockConfiguration;

void enableClocks(struct ClockConfiguration conf);

#endif //C0_RCC_H
