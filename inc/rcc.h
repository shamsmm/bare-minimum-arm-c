#ifndef C0_RCC_H
#define C0_RCC_H

#define RCC (volatile unsigned long *) 0x40021000

#define RCC_APB2ENR 6

#define IOPA 1 << 2
#define IOPB 1 << 3
#define IOPC 1 << 4

typedef struct ClockConfiguration {
    char offset;
    short value;
} ClockConfiguration;

void clockConfiguration(struct ClockConfiguration conf);

#endif //C0_RCC_H
