#include "bluepill.h"

void enablePLLAsSystemClock72MHz() {
    enablePLLAsSystemClockWithMultiplication(9);
}

void enablePLLAsSystemClock128MHz() {
    enablePLLAsSystemClockWithMultiplication(16);
}

void enablePLLAsSystemClock(ClockSpeed speed) {
    if (speed == PLL_Speed_128Mhz)
        enablePLLAsSystemClockWithMultiplication(16);
    else if (speed == PLL_Speed_72Mhz)
        enablePLLAsSystemClockWithMultiplication(9);
}