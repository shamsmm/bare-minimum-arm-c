#ifndef C0_SYSTEM_H
#define C0_SYSTEM_H

void system_disable_interrupts();
void system_enable_interrupts();
void system_svc_call(uint8_t);

#endif //C0_SYSTEM_H
