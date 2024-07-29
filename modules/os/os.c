#include <stdint.h>
#include <stdio.h>
#include "os.h"
#include "system/system.h"
#include "lcd_st7735/lcd.h"
#include "lcd_st7735/graphics/gfx.h"

volatile uint32_t Tick = 0;
uint8_t current_task = 255;
uint8_t os_start_scheduler = 0;
TCB_TypeDef tasks[TASK_COUNT];

_Alignas(8) uint32_t task1_stack[TASK_STACK_SIZE];
_Alignas(8) uint32_t task2_stack[TASK_STACK_SIZE];
_Alignas(8) uint32_t task3_stack[TASK_STACK_SIZE];

static inline void os_schedule() {
    *((volatile uint32_t *)0xE000ED04) = 0x10000000;
}

void SysTickHandler() {
    Tick++;
}

void task1() {
    uint16_t counter = 0;
    char buffer[100];

    while(1) {
        sprintf(buffer, "T1: %05u", counter++);
        ST7735_SetRotation(0);
        ST7735_WriteString(0, 0, buffer, Font_11x18, RED,BLACK);
        os_schedule();
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
        os_schedule();
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
        os_schedule();
    }
}

void os_init_task() {
    // Initialize task1 stack and context
    task1_stack[TASK_STACK_SIZE - 1] = 0x01000000;  // xPSR (Thumb state)
    task1_stack[TASK_STACK_SIZE - 2] = (uint32_t) task1 & ~0x01UL;  // PC (task entry point)
    task1_stack[TASK_STACK_SIZE - 3] = (uint32_t) 0xFFFFFFFD;  // LR (return to thread mode with PSP)
    tasks[0].stack_pointer = &task1_stack[TASK_STACK_SIZE - 16];  // Initial stack pointer

    // Initialize task2 stack and context
    task2_stack[TASK_STACK_SIZE - 1] = 0x01000000;  // xPSR (Thumb state)
    task2_stack[TASK_STACK_SIZE - 2] = (uint32_t) task2 & ~0x01UL;  // PC (task entry point)
    task2_stack[TASK_STACK_SIZE - 3] = (uint32_t) 0xFFFFFFFD;  // LR (return to thread mode with PSP)
    tasks[1].stack_pointer = &task2_stack[TASK_STACK_SIZE - 16];  // Initial stack pointer// Initialize task2 stack and context

    task3_stack[TASK_STACK_SIZE - 1] = 0x01000000;  // xPSR (Thumb state)
    task3_stack[TASK_STACK_SIZE - 2] = (uint32_t) task3 & ~0x01UL;  // PC (task entry point)
    task3_stack[TASK_STACK_SIZE - 3] = (uint32_t) 0xFFFFFFFD;  // LR (return to thread mode with PSP)
    tasks[2].stack_pointer = &task3_stack[TASK_STACK_SIZE - 16];  // Initial stack pointer

    os_start_scheduler = 1;
}

void SVCHandler() {
    __asm__ volatile ("msr psp, %0" : : "r" (&task1_stack[TASK_STACK_SIZE - 8]));

    __asm__ volatile ("ldr r0, =0xFFFFFFFD");

    __asm__ volatile ("bx r0");
}

void PendSVC() {
    // Save the current task context
    if (current_task == 255) {
        current_task = 1;
    } else {
        __asm__ volatile ("mrs %0, psp" : "=r" (tasks[current_task].stack_pointer));
        __asm__ volatile (
                "stmdb %0!, {r4-r11}"  // Store multiple registers onto the stack and update stack pointer
                : "=r" (tasks[current_task].stack_pointer)   // Output operand
                : "r" (tasks[current_task].stack_pointer)    // Input operand
                : "memory"             // Clobbered memory
                );
    }

    // Loop over the two tasks
    current_task = (current_task + 1) % TASK_COUNT;

    // Restore the next task context
    __asm__ volatile (
            "ldmia %0!, {r4-r11}"  // Load multiple registers from the stack and update stack pointer
            : "=r" (tasks[current_task].stack_pointer)        // Output operand
            : "r" (tasks[current_task].stack_pointer)         // Input operand
            : "memory"             // Clobbered memory
            );
    __asm__ volatile ("msr psp, %0" : : "r" (tasks[current_task].stack_pointer));

    __asm__ volatile ("ldr r0, =0xFFFFFFFD");

    __asm__ volatile ("bx r0");
}