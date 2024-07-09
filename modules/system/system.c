#include <stdint.h>
#include "system.h"

void system_disable_interrupts() {
    __asm__ volatile ("cpsid i");
}

void system_enable_interrupts() {
    __asm__ volatile ("cpsie i");
}

//void system_svc_call(uint8_t svc_number) {
//    __asm__ volatile ("svc %0" : : "I" (svc_number));
//}