#include <stdint.h>
#include <stdio.h>
#include "os.h"
#include "system/system.h"
#include "lcd_st7735/lcd.h"
#include "lcd_st7735/graphics/gfx.h"
#include "timer/systick.h"

volatile uint32_t Tick = 0;
uint32_t current_task = 0;
uint32_t os_start_scheduler = 0;
TCB_TypeDef tasks[TASK_COUNT];

_Alignas(8) uint32_t task1_stack[TASK_STACK_SIZE];
_Alignas(8) uint32_t task2_stack[TASK_STACK_SIZE];
_Alignas(8) uint32_t task3_stack[TASK_STACK_SIZE];
_Alignas(8) uint32_t task4_stack[TASK_STACK_SIZE];

uint32_t ** os_current_task_sp() {
    return &tasks[current_task].stack_pointer;
}

uint32_t ** os_next_task_sp() {
    current_task = (current_task + 1) % TASK_COUNT;
    return os_current_task_sp();
}

static inline void os_schedule() {
    *((volatile uint32_t *)0xE000ED04) = 0x10000000;
}

void SysTickHandler() {
    Tick++;

    if (os_start_scheduler)
        os_schedule();
}

void task1() {
    uint16_t counter = 0;
    char buffer[100];

    while(1) {
        sprintf(buffer, "T1: %05u", counter++);
        ST7735_SetRotation(0);
        ST7735_WriteString(0, 0, buffer, Font_11x18, RED,BLACK);
        //os_schedule();
    }
}

void task2() {
    uint16_t counter = 0;
    char buffer[100];

    while(1) {
        counter++;
        sprintf(buffer, "T2: %05u", counter++);
        ST7735_SetRotation(0);
        ST7735_WriteString(0, 18 + 1, buffer, Font_11x18, RED,BLACK);
        //os_schedule();
    }
}

void task3() {
    uint16_t counter = 0;
    char buffer[100];

    while(1) {
        counter++;
        counter++;
        sprintf(buffer, "T3: %05u", counter++);
        ST7735_SetRotation(0);
        ST7735_WriteString(0, 18 * 2 + 1, buffer, Font_11x18, RED,BLACK);
        //os_schedule();
    }
}

void task4() {
    while(1) {
        GPIO_WritePin(PC13, LOW);
        delay(1000);
        GPIO_WritePin(PC13, HIGH);
        delay(1000);
    }
}

void os_init_task() {
    // Initialize task1 stack and context
    task1_stack[TASK_STACK_SIZE - 1] = 0x01000000;  // xPSR (Thumb state)
    task1_stack[TASK_STACK_SIZE - 2] = (uint32_t) task1 & ~0x01UL;  // PC (task entry point)
    task1_stack[TASK_STACK_SIZE - 3] = (uint32_t) 0xFFFFFFFD;  // LR (return to thread mode with PSP)
    tasks[0].stack_pointer = &task1_stack[TASK_STACK_SIZE - 8 - 8];  // Initial stack pointer

    // Initialize task2 stack and context
    task2_stack[TASK_STACK_SIZE - 1] = 0x01000000;  // xPSR (Thumb state)
    task2_stack[TASK_STACK_SIZE - 2] = (uint32_t) task2 & ~0x01UL;  // PC (task entry point)
    task2_stack[TASK_STACK_SIZE - 3] = (uint32_t) 0xFFFFFFFD;  // LR (return to thread mode with PSP)
    tasks[1].stack_pointer = &task2_stack[TASK_STACK_SIZE - 8 - 8];  // Initial stack pointer// Initialize task2 stack and context

    task3_stack[TASK_STACK_SIZE - 1] = 0x01000000;  // xPSR (Thumb state)
    task3_stack[TASK_STACK_SIZE - 2] = (uint32_t) task3 & ~0x01UL;  // PC (task entry point)
    task3_stack[TASK_STACK_SIZE - 3] = (uint32_t) 0xFFFFFFFD;  // LR (return to thread mode with PSP)
    tasks[2].stack_pointer = &task3_stack[TASK_STACK_SIZE - 8 - 8];  // Initial stack pointer

    task4_stack[TASK_STACK_SIZE - 1] = 0x01000000;  // xPSR (Thumb state)
    task4_stack[TASK_STACK_SIZE - 2] = (uint32_t) task4 & ~0x01UL;  // PC (task entry point)
    task4_stack[TASK_STACK_SIZE - 3] = (uint32_t) 0xFFFFFFFD;  // LR (return to thread mode with PSP)
    tasks[3].stack_pointer = &task4_stack[TASK_STACK_SIZE - 8 - 8];  // Initial stack pointer

    os_start_scheduler = 1;
}

void SVCHandler() {
    __asm__ volatile ("msr psp, %0" : : "r" (&task1_stack[TASK_STACK_SIZE - 8]));

    __asm__ volatile ("ldr r0, =0xFFFFFFFD");

    os_start_scheduler = 1;

    __asm__ volatile ("bx r0");
}

void PendSVC2() {
}