#include <stdint.h>
#include "os.h"
#include "system/system.h"
#include "lcd_st7735/lcd.h"
#include "lcd_st7735/graphics/gfx.h"

uint8_t current_task = 0;
uint8_t ok = 0;
TCB_TypeDef tasks[TASK_COUNT];

uint32_t task1_stack[TASK_STACK_SIZE];
uint32_t task2_stack[TASK_STACK_SIZE];

void os_task_scheduler() {
    if (!ok)
        return;

    system_disable_interrupts();

    // Save the current task context
    __asm__ volatile ("mrs %0, psp" : "=r" (tasks[current_task].stack_pointer));
    __asm__ volatile ("stmdb %0!, {r4-r11, lr}" : : "r" (tasks[current_task].stack_pointer));


    // Loop over the two tasks
    current_task = (current_task + 1) % TASK_COUNT;

    // Restore the next task context
    __asm__ volatile ("ldmia %0!, {r4-r11, lr}" : : "r" (tasks[current_task].stack_pointer));
    __asm__ volatile ("msr psp, %0" : : "r" (tasks[current_task].stack_pointer));

    system_enable_interrupts();

    // When returning, the task will be resumed
}

// Should be alread in an exception
void os_task_scheduler_start() {

    ok = 1;
    // When returning, the task will start
}

void os_task_finished() {
    while (1) {

    }
}

void task1() {
    while(1) {
        fillScreen(BLACK);
        ST7735_SetRotation(0);
        ST7735_WriteString(0, 0, "task1", Font_11x18, RED,BLACK);
    }
}

void task2() {
    while(1) {
        ST7735_SetRotation(0);
        ST7735_WriteString(0, 0, "task2", Font_11x18, RED,BLACK);
        fillScreen(BLACK);
    }
}

void os_init_task() {
    // Initialize task1 stack and context
    task1_stack[TASK_STACK_SIZE - 1] = 0x01000000;  // xPSR (Thumb state)
    task1_stack[TASK_STACK_SIZE - 2] = (uint32_t) task1 & ~0x01UL;  // PC (task entry point)
    task1_stack[TASK_STACK_SIZE - 3] = (uint32_t) 0xFFFFFFFD;  // LR (return to thread mode with PSP)
    tasks[0].stack_pointer = &task1_stack[TASK_STACK_SIZE - 8];  // Initial stack pointer

    // Initialize task2 stack and context
    task2_stack[TASK_STACK_SIZE - 1] = 0x01000000;  // xPSR (Thumb state)
    task2_stack[TASK_STACK_SIZE - 2] = (uint32_t) task2;  // PC (task entry point)
    task2_stack[TASK_STACK_SIZE - 3] = (uint32_t) 0xFFFFFFFD;  // LR (return to thread mode with PSP)
    tasks[1].stack_pointer = &task2_stack[TASK_STACK_SIZE - 8];  // Initial stack pointer
}

void os_task_yield() {
//    system_svc_call(0);
}

void SVCHandler() {
    __asm__ volatile ("msr psp, %0" : : "r" (tasks[current_task].stack_pointer));
//    __asm__ volatile ("msr control, %0" : : "r" (0x2)); // Switch to use PSP
//    __asm__ volatile ("isb"); // Synchronization
    __asm__ volatile ("mov lr, %0" : : "r" (0xFFFFFFFD));


}

void PendSVC() {
    (void) 1;
}