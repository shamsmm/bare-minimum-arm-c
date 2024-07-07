#ifndef C0_LCD_1602_H
#define C0_LCD_1602_H

#include "i2c.h"

extern void delay(int);

void LCD_1602_I2C_Init();
void LCD_1602_I2C_Write(char * ptr);

#endif //C0_LCD_1602_H
