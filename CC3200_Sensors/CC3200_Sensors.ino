
//Required for BMA222 Accelerometer sensor
#include "BMA222.h"
#include "LCD16x2.h"


// Define external sensors, inputs and outputs.
BMA222 accSensor;            // Three axis acceleration sensor

LCD16x2 mylcd;
const char ADCLCDSTRING[] = "ADC: %i\r\n";
// DO NOT Exceed 1.5V on the analogue input pin
#define ANALOGPIN 6     // Labelled P59 on CC3200 Lauchpad.
//Include libraries required for TMP006 Temperature sensor and create instance
#include <Wire.h>
#include "Adafruit_TMP006.h"
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
  
  mylcd.begin(0x3E);
  mylcd.writeString(0,0,"Hello");
}

// Main loop. Runs continuously
void loop() {
    char string[9];
  // DO NOT Exceed 1.5V on the analogue input pin
    sprintf(string, ADCLCDSTRING, analogRead(ANALOGPIN));
    Serial.print("Object (Die) Temperature: ");
    Serial.print(tmp006.readObjTempC());
    Serial.print((char)176);                //Print degree symbol
    Serial.print("C (");
    Serial.print(tmp006.readDieTempC());
    Serial.print((char)176);                //Print degree symbol
    Serial.println("C)");
    Serial.print("Acc X: ");
    Serial.print(accSensor.readXData());
    Serial.print(", Y: ");
    Serial.print(accSensor.readYData());
    Serial.print(", Z: ");
    Serial.print(accSensor.readZData());
    Serial.print(string);
    
    mylcd.writeString(1,0,string);

  delay(5000);
}


