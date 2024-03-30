#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"

void wait() {
    for (unsigned int i = 0; i < 100000; ++i) __asm__ volatile ("nop");
}

static char led = 1;
void main() {
    GPIO_InitTypeDef init;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_StructInit(&init);
    init.GPIO_Pin = GPIO_Pin_13;
    init.GPIO_Mode = GPIO_Mode_Out_PP;
    init.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &init);

    while (1) {
        // Set the output bit.
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, led ? Bit_SET : Bit_RESET);

        wait();
        led = !led;
    }
}
