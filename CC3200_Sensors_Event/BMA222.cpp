/*
 ************************************************************************
 *	BMA222.cpp
 *	Version 1.0
 *
 *	Energia Library/Arduino for the BMA222 accelerometer
 *		Copyright (c) 2014 Robert Wessels. All right reserved.
 *
 ***********************************************************************
  Copyright (c) 2014 Robert Wessels.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  
  modified Benn Thomsen
*/

#include "Energia.h"
#include "BMA222.h"

BMA222::BMA222() {}
BMA222::~BMA222() {}

void BMA222::begin(uint8_t addr)
{
	i2cAddr = addr;
	Wire.begin();
}

// Reads a single byte from reg
int8_t BMA222::readReg(uint8_t reg)
{
	Wire.beginTransmission(i2cAddr);
	Wire.write(reg);
	Wire.endTransmission();

	Wire.requestFrom(i2cAddr, (uint8_t) 1);
	if(Wire.available()) {
		return Wire.read();
	}

	return 0;
}

// Writes a single byte (dataToWrite) into reg
void BMA222::writeReg(uint8_t reg, uint8_t dataToWrite)
{
  Wire.beginTransmission(i2cAddr);
  Wire.write(reg);
  Wire.write(dataToWrite);
  Wire.endTransmission(); //Stop transmitting
}

void BMA222::begin()
{
	begin(BMA222_DEV_ADDR);
}

uint8_t BMA222::chipID()
{
	return (uint8_t )readReg(BMA222_CHIP_ID_REG);
}

int16_t BMA222::readXData()
{
	return readReg(BMA222_ACC_DATA_X);
}

int16_t BMA222::readYData()
{
	return readReg(BMA222_ACC_DATA_Y);
}

int16_t BMA222::readZData()
{
	return readReg(BMA222_ACC_DATA_Z);
}

double BMA222::readTemp()
{
    return 0.5*readReg(BMA222_TEMP)+24.0;
}

uint8_t BMA222::intStatus()
{
	return (uint8_t )readReg(BMA222_INT_STATUS);
}

uint8_t BMA222::range()
{
	return (uint8_t )readReg(BMA222_RANGE);
}

void BMA222::range(uint8_t range)
{
	writeReg(BMA222_RANGE,range);
}

void BMA222::singleTapInterrupt()
{
        writeReg(BMA222_INT_0,s_tap_enable);
        writeReg(BMA222_INT_PINMAP,int1_s_tap);
}
