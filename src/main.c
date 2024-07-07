#include "gpio.h"
#include "rcc.h"
#include "bluepill.h"
#include "oled.h"
#include "systick.h"
#include "lcd.h"
#include "adc.h"
#include "spi.h"
#include "ST7735.h"
#include "GFX_FUNCTIONS.h"

//#define SYSTICK_CLKSOURCE_EXTERNAL
#define SYSTICK_CLKSOURCE_INTERNAL

volatile unsigned long Tick = 0;

// duration is in number of nop instructions, not time
void SysTick_Handler() {
    Tick++;
}

void delay(int milliseconds) {
    unsigned long initial = Tick;
    while (Tick - initial < milliseconds);
}

void main() {
    enablePLLAsSystemClock(PLL_Speed_128Mhz);

#if defined(SYSTICK_CLKSOURCE_EXTERNAL)
    SysTickReloadValue = 8000; // Clock source is external 8MHz
#elif defined(SYSTICK_CLKSOURCE_INTERNAL)
    SysTickControlAndStatus->CLKSOURCE = 1;
    SysTickReloadValue = 64000; // Clock source is AHB which is 64MHz
#endif
    SysTickControlAndStatus->TICKINT = 1;
    SysTickControlAndStatus->ENABLE = 1;

    enableClocks(BLUEPILL_ALL_APB2_INTERFACES_CLOCK);
    enableClocks(BLUEPILL_ALL_APB1_INTERFACES_CLOCK);

//    pinMode(PA8, ALTERNATE_PUSH_PULL);
    pinMode(PA9, ALTERNATE_PUSH_PULL);
    pinMode(PC13, OUTPUT_ULTRA_FAST);

    pinMode(PA2, OUTPUT_ULTRA_FAST);
    pinMode(PB6, OUTPUT_ULTRA_FAST);
    pinMode(PB11, OUTPUT_ULTRA_FAST);

    pinMode(PA7, ALTERNATE_PUSH_PULL);
    pinMode(PA5, ALTERNATE_PUSH_PULL);

    delay(100);

    SPI1->CR1.MSTR = 1;
    SPI1->CR1.BR = 3;
    SPI1->CR1.BIDIMODE = 1;
    SPI1->CR1.BIDIOE = 1;
    SPI1->CR1.SSI = 1;
    SPI1->CR1.SSM = 1;
    SPI1->CR1.SPE = 1;

    delay(100);

    ST7735_Init(0);
    fillScreen(BLACK);

    digitalWrite(PC13, HIGH);
    while(1) {
        SPI_Transmit_Byte(SPI1, 0xAA);
    }
}