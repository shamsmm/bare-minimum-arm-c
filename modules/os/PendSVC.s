    .section .text.os
    .global PendSVC

    .extern tasks
    .extern current_task
    .thumb_func
    .syntax unified
PendSVC:
    // Save the current task context
    mrs r0, psp
    ldr r1, =current_task
    ldr r1, [r1]
    ldr r2, =tasks
    ldr r2, [r2, r1, lsl #2]
    str r0, [r2]

    // Save r4-r11
    stmdb r0!, {r4-r11}
    str r0, [r2]

    // Loop over the two tasks
    ldr r1, =current_task
    ldr r2, [r1]
    add r2, r2, #1
    mov r3, #3
    cmp r2, r3
    it ge
    movge r2, #0
    str r2, [r1]

    // Restore the next task context
    ldr r1, =tasks
    ldr r2, [r1, r2, lsl #2]
    ldr r0, [r2]
    ldmia r0!, {r4-r11}
    str r0, [r2]

    // Set PSP to the new task's stack pointer
    msr psp, r0

    // Return to thread mode using the PSP
    ldr r0, =0xFFFFFFFD
    bx r0