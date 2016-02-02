#include "Energia.h"
#include <Wire.h>

#ifndef BMA222_h
#define BMA222_h
#endif

#define BMA222_DEV_ADDR 0x18
#define BMA222_CHIP_ID_REG 0x00

#define BMA222_ACC_DATA_X_NEW (0x2)
#define BMA222_ACC_DATA_X     (0x3)
#define BMA222_ACC_DATA_Y_NEW (0x4)
#define BMA222_ACC_DATA_Y     (0x5)
#define BMA222_ACC_DATA_Z_NEW (0x6)
#define BMA222_ACC_DATA_Z     (0x7)
#define BMA222_TEMP           (0x8)
#define BMA222_INT_STATUS     (0x9)

#define BMA222_RANGE          (0xF)
#define BMA222_INT_0          (0x16)
#define BMA222_INT_1          (0x17)

#define BMA222_INT_PINMAP     (0x19)

//Range values
#define RANGE_2G              (0b0011)
#define RANGE_4G              (0b0101)
#define RANGE_8G              (0b1000)
#define RANGE_16G             (0b1100)

//Interrupt Types
#define s_tap_enable          (0x20)
#define int1_s_tap            (0x20)



class BMA222 {
private:
	uint8_t i2cAddr;
public:

	BMA222();
	~BMA222();
	void begin();
	void begin(uint8_t addr);
	int8_t readReg(uint8_t reg);
        void writeReg(uint8_t reg, uint8_t dataToWrite);
	uint8_t chipID();
	int16_t readXData();
	int16_t readYData();
	int16_t readZData();
        double readTemp();
        uint8_t intStatus();
        uint8_t range();
        void range(uint8_t range);
        void singleTapInterrupt();
};
