#include "rtosGlobals.h"
#include "Event.h"

//Required for BMA222 Accelerometer sensor
#include "BMA222.h"




// Define external sensors, inputs and outputs.
BMA222 accSensor;            // Three axis acceleration sensor

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
  
  accSensor.range(RANGE_2G);
  Serial.println(accSensor.range());
  
  myEvent.begin();
  accSensor.singleTapInterrupt();
  pinMode(PUSH1,INPUT);
  attachInterrupt(PUSH1, acc_int, RISING); // Interrupt is fired whenever button is pressed
  

}

// Main loop. Runs continuously
void loop() {
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
    Serial.println(accSensor.readZData());
    Serial.print("Acc Temp:  ");
    Serial.println(accSensor.readTemp());

    delay(15000);
}

// Rising edge interrupt function
void acc_int(){
  myEvent.send();
}


