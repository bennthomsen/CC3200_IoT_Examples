
//Required for BMA222 Accelerometer sensor
#include <BMA222.h>
//Required for TMP006 Temperature sensor
#include <Wire.h>
#include "Adafruit_TMP006.h"

// Define external sensors, inputs and outputs.
BMA222 accSensor;            // Three axis acceleration sensor
Adafruit_TMP006 tmp006(0x41);

// Setup function runs once when microprocessor is powered up
void setup() {
  Serial.begin(115200);          //Initialise serial port for local monitoring on the Serail Monitor via USB
  
// Start Temperature Sensor
  if (!tmp006.begin()) {
    Serial.println("No sensor found");
    while (1);
  }
  
// Start the accel sensor
  accSensor.begin();
  uint8_t chipID = accSensor.chipID();
  Serial.print("ChipID: ");
  Serial.println(chipID);
}

// Main loop. Runs continuously
void loop() {
    Serial.print("Object Temperature: ");
    Serial.println(tmp006.readObjTempC());
    Serial.print("Die Temperature: ");
    Serial.println(tmp006.readDieTempC());
    Serial.print("Acc X: ");
    Serial.print(accSensor.readXData());
    Serial.print(", Y:");
    Serial.print(accSensor.readYData());
    Serial.print(", Z:");
    Serial.println(accSensor.readZData());

    delay(1000);
}


