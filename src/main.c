#include "main.h"
#include "gpio.h"
#include "rcc.h"
#include "../modules/bluepill/inc/bluepill.h"
#include "../modules/oled_ssd1306/inc/oled.h"
#include "../modules/timer/inc/systick.h"
#include "../modules/lcd_1602/inc/lcd_1602.h"
#include "../modules/adc/inc/adc.h"
#include "spi.h"
#include "../modules/lcd_st7735/inc/lcd_st7735.h"
#include "../modules/lcd_st7735/inc/lcd_st7735/gfx.h"

//#define SYSTICK_CLKSOURCE_EXTERNAL
#define SYSTICK_CLKSOURCE_INTERNAL

volatile unsigned long Tick = 0;

// duration is in number of nop instructions, not time
void SysTickHandler() {
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
        ST7735_WriteString(0, 0, "HELLO", Font_11x18, RED,BLACK);
        delay(500);
    }
}