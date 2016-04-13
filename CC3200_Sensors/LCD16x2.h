/*
CC3200      LCD
VCC -------- VCC
RST -------- RST
P01 -------- SCL
P02 -------- SDA
VCC -------- BL
GND -------- VSS

*/
#include "Energia.h"
#include <Wire.h>

#ifndef LCD16x2_h
#define LCD16x2_h
#endif

#define BACKLIGHT 12
#define BLINK 0x01
#define CURSOR 0x02
#define DISPLAYMEM 0x80


class LCD16x2 {
private:
	uint8_t i2cAddr;
        char _display[2];
        uint8_t line;
        uint8_t _column;
public:

	LCD16x2();
        ~LCD16x2();
	void begin(uint8_t);
        void home(void);
        void clear(void);
        void blinkOn();                    //Turn blinking cursor on
        void blinkOff();                   //Turn blinking cursor off
        void cursorOn();                   //Turn cursor on
        void cursorOff();                  //Turn cursor off
        void writeString(char*);           //Write string at current cursor position
        void writeString(uint8_t, uint8_t, char*);           //Write string at current cursor position
};
