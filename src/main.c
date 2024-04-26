#include "gpio.h"
#include "rcc.h"
#include "bluepill.h"
#include "adc.h"
#include "i2c.h"



// duration is in number of nop instructions, not time
void delay(int duration) {
    for (unsigned int i = 0; i < duration; ++i) __asm__ volatile ("nop");
}

unsigned short int value;

void main() {
    enablePLLAsSystemClock(PLL_Speed_128Mhz);
    enableClocks(BLUEPILL_ALL_APB2_INTERFACES_CLOCK);
    enableClocks(BLUEPILL_ALL_APB1_INTERFACES_CLOCK);

    pinMode(PB6, ALTERNATE_OPEN_DRAIN);
    pinMode(PB7, ALTERNATE_OPEN_DRAIN);

    pinMode(PC13, OUTPUT_ULTRA_FAST);

    I2C_CR1->SWREST = 1;
    I2C_CR1->SWREST = 0;
    I2C_CR1->PE = 0;

    I2C_CR2->FREQ = 32; // Set APB1 frequency to 32MHz as set by RCC
    I2C_CCR->CCR = 160; // 2 * CCR * T_APB1 = 1/100KHz
//    I2C_TRISE->TRISE = 0;

    I2C_CR1->PE = 1;

    while(1) {
        while (I2C_SR2->BUSY);

        I2C_CR1->ACK = 1;
        I2C_CR1->START = 1;

        while(!I2C_SR1->SB);

        I2C_DR = 0x78; // Slave Address
        while (!I2C_SR1->ADDR);

        volatile unsigned long t = I2C_SR1->BTF | I2C_SR2->BUSY;

        while (!I2C_SR1->TxE);
        I2C_DR = 0xAA; // Data
        while (!I2C_SR1->BTF);
        I2C_CR1->STOP = 1;

        delay(200000);
        digitalWrite(PC13, HIGH);
        delay(200000);
        digitalWrite(PC13, LOW);
    }
}