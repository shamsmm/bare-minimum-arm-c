.section .isr_vectors

isr_vectors:
    .word _estack           // Supplied by the linker
    .word Reset_Handler     // This function has to be specified as .thumb_func
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word SysTick_Handler

.section .text.Reset_Handler
.global Reset_Handler

.thumb_func
Reset_Handler:
    bl CopyDataInit
    bl main
halt:
    b halt

CopyDataInit:
    ldr r0, =_sidata
    ldr r1, =_sdata
    ldr r2, =_edata
LoopCopyDataInit:
    cmp r1, r2
    bge CopyDataInitReturn
    ldr r3, [r0]
    str r3, [r1]
    add r0, r0, #4
    add r1, r1, #4
    b LoopCopyDataInit
CopyDataInitReturn:
    bx lr

.weak	SysTick_Handler
.set	SysTick_Handler, Default_Handler
.thumb_func
Default_Handler:
    b .