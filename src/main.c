#include <malloc.h>
#include <stdio.h>

#include "gpio/gpio.h"
#include "rcc/rcc.h"
#include "bluepill/bluepill.h"
#include "timer/systick.h"
#include "spi/spi.h"
#include "lcd_st7735/lcd.h"
#include "lcd_st7735/graphics/gfx.h"
#include "os/os.h"
#include "mpu/mpu.h"

//#define SYSTICK_CLKSOURCE_EXTERNAL
#define SYSTICK_CLKSOURCE_INTERNAL

void delay(int milliseconds) {
    unsigned long initial = Tick;
    while (Tick - initial < milliseconds/10);
}

void main() {
    enablePLLAsSystemClock(PLL_Speed_128Mhz);

#if defined(SYSTICK_CLKSOURCE_EXTERNAL)
    SysTickReloadValue = 8000; // Clock source is external 8MHz
#elif defined(SYSTICK_CLKSOURCE_INTERNAL)
    SysTickControlAndStatus->CLKSOURCE = 1;
    SysTickReloadValue = 640000; // Clock source is AHB which is 64MHz
#endif
    SysTickControlAndStatus->TICKINT = 1;
    SysTickControlAndStatus->ENABLE = 1;

    enableClocks(BLUEPILL_ALL_APB2_INTERFACES_CLOCK);
    enableClocks(BLUEPILL_ALL_APB1_INTERFACES_CLOCK);

//    pinMode(PA8, ALTERNATE_PUSH_PULL);
    GPIO_PinMode(PA9, ALTERNATE);
    GPIO_PinMode(PC13, OUTPUT);

    GPIO_PinMode(PA2, OUTPUT);
    GPIO_PinMode(PB6, OUTPUT);
    GPIO_PinMode(PB11, OUTPUT);

    GPIO_PinMode(PA7, ALTERNATE);
    GPIO_PinMode(PA5, ALTERNATE);

    delay(100);

    SPI1->CR1.MSTR = 1;
    SPI1->CR1.BR = 0;
    SPI1->CR1.BIDIMODE = 1;
    SPI1->CR1.BIDIOE = 1;
    SPI1->CR1.SSI = 1;
    SPI1->CR1.SSM = 1;
    SPI1->CR1.SPE = 1;

    delay(100);

    ST7735_Init(0);
    fillScreen(BLACK);

    GPIO_WritePin(PC13, HIGH);

    uint32_t *pSHCSR = (uint32_t*)0xE000ED24;

    *pSHCSR |= ( 1 << 16); //mem manage
    *pSHCSR |= ( 1 << 17); //bus fault
    *pSHCSR |= ( 1 << 18); //usage fault

    // Enable the MPU
    MPU->CTRL = 0;

    // Configure the region for the peripheral access
    MPU->RNR = 0;
    MPU->RBAR = 0x40000000; // Base address of the peripheral space
    MPU->RASR = (0x3 << 24) | // Full access
                (0x1 << 19) | // Enable the region
                (0x0 << 8)  | // Memory type: Normal
                (0x0 << 4)  | // Sub-region disabled
                (0x7 << 1)  | // Size = 512MB (Peripheral space)
                (0x1 << 0);   // Enable region

    // Enable the MPU, use the default memory map as background
    MPU->CTRL = 1 << 2 | 1 << 0;

    __asm__ volatile ("svc %0" : : "I" (0));

    os_init_task();

    while (1) {
    }
}