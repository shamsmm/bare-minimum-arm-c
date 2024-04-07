#include "bluepill.h"

unsigned short analogRead(GPIO gpio) {
    return analogReadInterface(ADC1, gpio);
}
