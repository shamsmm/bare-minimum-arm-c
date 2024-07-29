#ifndef C0_OS_H
#define C0_OS_H

#define TASK_COUNT 4
#define TASK_STACK_SIZE 0x100

extern volatile uint32_t Tick;

typedef struct TCB {
    uint32_t * stack_pointer;
    // Add other task-specific data here
} TCB_TypeDef;

void os_task_scheduler();
void os_task_scheduler_start();
void os_init_task();

uint32_t os_next_task();

#endif //C0_OS_H
