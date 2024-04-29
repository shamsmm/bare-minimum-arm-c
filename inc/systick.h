#ifndef C0_SYSTICK_H
#define C0_SYSTICK_H

#define SysTickControlAndStatus ((volatile SysTickControlAndStatusTypeDef*) 0xE000E010)
#define SysTickReloadValue *((volatile unsigned long*) 0xE000E014)
#define SysTickCurrentValue *((volatile unsigned long*) 0xE000E018)

typedef struct SysTickControlAndStatusTypeDef {
    unsigned long ENABLE   :1,
                  TICKINT  :1,
                  CLKSOURCE:1,
                           :13,
                  COUNTFLAG:1,
                           :15;
} SysTickControlAndStatusTypeDef;

#endif //C0_SYSTICK_H
