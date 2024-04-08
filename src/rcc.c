#include "rcc.h"
#include "common.h"

#define HSEON 16
#define HSERDY 17
#define PLLON 24
#define PLLRDY 25

#define PLLMUL 18
#define PLLSRC 16
#define MCO 24
#define ADCPRE 14
#define HPRE 4

#define FLASH_INTERFACE (unsigned long *) 0x40022000

void enableClocks(ClockConfiguration conf) {
    *(RCC + conf.offset) |= conf.value;
}

void disableClocks(ClockConfiguration clockConfiguration) {
    *(RCC + clockConfiguration.offset) &= ~clockConfiguration.value;
}

void enablePLLAsSystemClockWithMultiplication(byte mul) {
    *RCC |= 1 << HSEON;

    while (!(*RCC >> HSERDY & 1))
        __asm__ volatile("nop");

//    *(RCC + RCC_CFGR) |= 7 << PLLMUL; // 7 for x9
    *(RCC + RCC_CFGR) |= (mul - 2) << PLLMUL; // 15 for x16 128MHz
    *(RCC + RCC_CFGR) |= 1 << PLLSRC;
    *(RCC + RCC_CFGR) |= 4 << MCO;

    *RCC |= 1 << PLLON;

    while (!(*RCC >> PLLRDY & 1))
        __asm__ volatile("nop");

    *FLASH_INTERFACE |= 0b10010;
    *(RCC + RCC_CFGR) |= 3 << ADCPRE;

    *(RCC + RCC_CFGR) |= 8 << HPRE;
    *(RCC + RCC_CFGR) |= 2;

    while ((*(RCC + RCC_CFGR) & 0b1010) != 0b1010)
        __asm__ volatile("nop");
}