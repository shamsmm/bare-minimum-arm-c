#include "rcc.h"

void clockConfiguration(struct ClockConfiguration conf) {
    *(RCC + conf.offset) |= conf.value;
}

void clockConfigurationDisable(struct ClockConfiguration clockConfiguration) {
    *(RCC + clockConfiguration.offset) &= ~clockConfiguration.value;
}