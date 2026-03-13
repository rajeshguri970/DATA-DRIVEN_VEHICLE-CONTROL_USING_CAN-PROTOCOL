//lcd.h
#ifndef _LCD_H
#define _LCD_H

#include "types.h"

void writeLCD(u8 byte);
void cmdLCD(u8 cmd);
void initLCD(void);
void charLCD(u8 ascii);
void strLCD(u8 *);
void u32LCD(u32);
void s32LCD(s32);
void f32LCD(f32,u32);
void setcurpos(u8,u8);
void buildCGRAM(u8 *,u8);

#endif
