#include "rcc.h"

void enableClocks(ClockConfiguration conf) {
    *(RCC + conf.offset) |= conf.value;
}

void disableClocks(ClockConfiguration clockConfiguration) {
    *(RCC + clockConfiguration.offset) &= ~clockConfiguration.value;
}