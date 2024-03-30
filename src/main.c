#include <malloc.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"

void wait() {
    for (unsigned int i = 0; i < 100000; ++i) __asm__ volatile ("nop");
}

extern const char led[];
void main() {
    GPIO_InitTypeDef init;
    volatile char* updated = malloc(sizeof(char) * 55000000000000);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_StructInit(&init);
    init.GPIO_Pin = GPIO_Pin_13;
    init.GPIO_Mode = GPIO_Mode_Out_PP;
    init.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &init);
    int z = 0;
    while (1) {
        // Set the output bit.
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, led[z] ? Bit_SET : Bit_RESET);

        wait();
//        led = !led;
        z++;
        if (z > 4)
            z=0;
    }
}
