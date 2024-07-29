    .section .text.os
    .global PendSVC

    .extern tasks
    .extern current_task
    .extern os_next_task
    .thumb_func
    .syntax unified
PendSVC:
    // Store current context
    mrs r0, psp
    stmdb r0!, {r4-r11}
    ldr r1, =current_task
    ldr r1, [r1]
    ldr r2, =tasks
    str r0, [r2, r1, lsl 2]

    // Get the next task
    bl os_next_task

    // Restore the next task context
    ldr r2, =tasks
    ldr r0, [r2, r0, lsl 2]
    ldmia r0!, {r4-r11}
    str r0, [r2]

    // Set PSP to the new task's stack pointer
    msr psp, r0

    // Return to thread mode using the PSP
    ldr r0, =0xFFFFFFFD
    bx r0