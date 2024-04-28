#ifndef C0_OLED_H
#define C0_OLED_H

#include "fonts.h"
#include "i2c.h"

#define OLED_7Bit_ADDRESS 0x3C
#define CONTROL_BYTE 0x00
#define DATA_BYTE 0x40

void OLED_I2C_Init();
void OLED_I2C_Draw(const char * ptr, int length);
void OLED_I2C_Write(unsigned char col, unsigned char page, char * ptr);

#endif //C0_OLED_H
