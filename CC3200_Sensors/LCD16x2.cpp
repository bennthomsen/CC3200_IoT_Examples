#include "Energia.h"
#include "LCD16x2.h"

LCD16x2::LCD16x2() {}
LCD16x2::~LCD16x2() {}

void LCD16x2::begin(uint8_t addr)
{
	i2cAddr = addr;
	Wire.begin();
  const unsigned char TxData[] =              // Table of data to transmit
  { 0x00,
    0x38,
    0x00,
    0x39,
    0x14,
    0x70,
    0x54,
    0x6F,
    0x0F, //Display On, Cursor On, Cursor Blink On
    0x01};
  Wire.begin(); // join i2c bus (address optional for master)
  Wire.beginTransmission(i2cAddr);  // transmit to device address 0x3E
  Wire.write(TxData,10);           // send initialisation commands  
  Wire.endTransmission();     // stop transmitting
  _display[0] = 0x80;
  _display[1] = 0x0F;
  line=0x00;
}

void LCD16x2::home(void)
{
  Wire.beginTransmission(i2cAddr); // transmit to device #44 (0x2c)
  Wire.write(0x80);            // Send instruction control byte
  Wire.write(0x02);
  Wire.endTransmission();     // stop transmitting
}

void LCD16x2::clear()
{
  Wire.beginTransmission(i2cAddr); // transmit to device #44 (0x2c)
  Wire.write(byte(0x80));            // Send instruction control byte
  Wire.write(0x01);
  Wire.endTransmission();     // stop transmitting
}

void LCD16x2::writeString(char *data)
// Writes a string at the current cursor position
{
  Wire.beginTransmission(i2cAddr);  // transmit to device #44 (0x2c)
  //Wire.write(byte(0x80));            // Send command control
  //Wire.write(_line);                 // Memory Location instruction
  Wire.write(byte(0x40));            // Send character control byte
  delay(1);
  Wire.write(data);
  Wire.endTransmission();     // stop transmitting 
}

void LCD16x2::writeString(uint8_t row, uint8_t column, char *data)
// Writes a string at the column position specified
{
  if (row) line = 0x40;
    else line = 0x00;
  Wire.beginTransmission(i2cAddr);  // transmit to device #44 (0x2c)
  Wire.write(byte(0x80));            // Send command control
  line+=column;
  Wire.write(DISPLAYMEM | line);     // Memory Location instruction
  Wire.write(byte(0x40));            // Send character control byte
  delay(1);
  Wire.write(data);
  Wire.endTransmission();     // stop transmitting 
}


void LCD16x2::blinkOn()
{
  Wire.beginTransmission(i2cAddr); // transmit to device
  _display[1] |=BLINK;
  Wire.write(_display);
  Wire.endTransmission();           // stop transmitting
}

void LCD16x2::blinkOff()
{
  Wire.beginTransmission(i2cAddr); // transmit to device
  _display[1] &= ~BLINK;
  Wire.write(_display);
  Wire.endTransmission();           // stop transmitting
}

void LCD16x2::cursorOn()
{
  Wire.beginTransmission(i2cAddr); // transmit to device
  _display[1] |=CURSOR;
  Wire.write(_display);
  Wire.endTransmission();           // stop transmitting
}

void LCD16x2::cursorOff()
{
  Wire.beginTransmission(i2cAddr); // transmit to device #44 (0x2c)
  _display[1] &= ~CURSOR;
  Wire.write(_display);
  Wire.endTransmission();           // stop transmitting
}

