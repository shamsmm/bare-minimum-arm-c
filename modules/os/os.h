#ifndef C0_OS_H
#define C0_OS_H

#define TASK_COUNT 4
#define TASK_STACK_SIZE 0x200

extern volatile uint32_t Tick;

typedef struct TCB {
    uint32_t * stack_pointer;
    // Add other task-specific data here
} TCB_TypeDef;

void os_init_tasks();
void os_enable_preemption();
void os_disable_preemption();

#define OS_TASK_LOCK()      extern uint32_t os_preemption_status;\
                            uint32_t preemption_status = os_preemption_status;\
                            os_disable_preemption()

#define OS_TASK_UNLOCK()  if (preemption_status)\
                            os_enable_preemption()
#endif //C0_OS_H
