#include "bluepill.h"

unsigned short analogRead(GPIO gpio) {
    return gpio.adc == NC ? 0 : analogReadInterface(ADC1, gpio.adc);
}
