#include "gpio.h"
#include "rcc.h"
#include "bluepill.h"
#include "oled.h"
#include "systick.h"
#include "lcd.h"

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

    pinMode(PB6, ALTERNATE_OPEN_DRAIN);
    pinMode(PB7, ALTERNATE_OPEN_DRAIN);

    pinMode(PC13, OUTPUT_ULTRA_FAST);

    delay(1000);

    I2C_Init();
    OLED_I2C_Init();
    LCD_1602_I2C_Init();

    OLED_I2C_Write(0, 0, "Hi");
    OLED_I2C_Write(0, 1, "There :)");
    OLED_I2C_Write(0, 2, "I am");
    OLED_I2C_Write(0, 3, "Coo00000***L");

    LCD_1602_I2C_Write("Yes I slept");

    while(1) {
        digitalWrite(PC13, HIGH);
        delay(500);
        digitalWrite(PC13, LOW);
        delay(500);
    }
}