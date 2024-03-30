#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"

#define DELAY_DURATION 150000
#define MESSAGE_LENGTH 9

void RCC_Configuration(void);
void GPIO_Configuration(void);

USART_InitTypeDef uart;
GPIO_InitTypeDef gpio;

// Message to be sent through uart
const char buffer[MESSAGE_LENGTH] = "Hi there!";

// duration is in number of nop instructions, not time
void wait() {
    for (unsigned int i = 0; i < DELAY_DURATION; ++i) __asm__ volatile ("nop");
}

void main(void) {
    RCC_Configuration();
    GPIO_Configuration();

    // Initialize UART1
    uart.USART_BaudRate = 9600;
    uart.USART_WordLength = USART_WordLength_8b;
    uart.USART_StopBits = USART_StopBits_1;
    uart.USART_Parity = USART_Parity_No;
    uart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    uart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1 ,&uart);
    USART_Cmd(USART1, ENABLE);


    while(1) {
        // Blink an LED while transmission
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);

        wait();

        // Transmit message
        int i = 0;
        while(i < MESSAGE_LENGTH) {
            USART_SendData(USART1, buffer[i++]);
            // Wait for buffer to be sent before sending new characters
            while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
            {
            }
        }

        // Send a newline
        USART_SendData(USART1, '\n');

        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
        wait();
    }
}

void RCC_Configuration(void) {
    // Enable Clock for UART, GPIOA which has UART AF pin, GPIOC for onboard LED
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
}

void GPIO_Configuration(void) {
    // PA9 as TX
    gpio.GPIO_Pin = GPIO_Pin_9;
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio);

    // PC13 as blinking LED
    gpio.GPIO_Pin = GPIO_Pin_13;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &gpio);
}