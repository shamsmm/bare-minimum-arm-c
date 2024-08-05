#include <cstdio>
#include "gpio/gpio.h"
#include "rcc/rcc.h"
#include "bluepill/bluepill.h"
#include "timer/systick.h"
#include "spi/spi.h"
#include "lcd_st7735/lcd.h"
#include "lcd_st7735/graphics/gfx.h"
#include "os/os.h"
#include "system/system.h"
#include "app/Application.h"

//#define SYSTICK_CLKSOURCE_EXTERNAL
#define SYSTICK_CLKSOURCE_INTERNAL



void enable_spi_for_lcd() {
    SPI1->CR1.MSTR = 1;
    SPI1->CR1.BR = 0;
    SPI1->CR1.BIDIMODE = 1;
    SPI1->CR1.BIDIOE = 1;
    SPI1->CR1.SSI = 1;
    SPI1->CR1.SSM = 1;
    SPI1->CR1.SPE = 1;
}

int main() {
    enablePLLAsSystemClock(PLL_Speed_128Mhz);
    system_faults_configure();

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

    GPIO_PinMode(PA8, ALTERNATE); // To expose system clock
    GPIO_PinMode(PA9, ALTERNATE); // TX and RX
    GPIO_PinMode(PA10, ALTERNATE); // TX and RX
    GPIO_PinMode(PC13, OUTPUT); // LED

    enableUART(USART1, 64000000, 9600);

    GPIO_PinMode(PA2, OUTPUT);
    GPIO_PinMode(PB6, OUTPUT);
    GPIO_PinMode(PB11, OUTPUT);

    GPIO_PinMode(PA7, ALTERNATE);
    GPIO_PinMode(PA5, ALTERNATE);

    delay(100);

    enable_spi_for_lcd();

    delay(500);

    ST7735_Init(0);
    fillScreen(BLACK);

    GPIO_WritePin(PC13, HIGH);
    UART_Transmit_Line(USART1, "ABooooooooooood");
    printf("OS initializing tasks");
    os_init_tasks();

    printf("Context switching to first task");
    __asm__ volatile ("svc %0" : : "I" (0));

    while (1) {
        auto * app = new Application();
        app->test();
    }
}