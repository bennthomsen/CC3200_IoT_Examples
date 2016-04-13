/*
  Energia library for DHT11 and DHT22/RHT03/AM2302
  
  Modified by Benn Thomsen, April 2016 from original source
  https://github.com/MORA99/Stokerbot/tree/master/Libraries/dht
  Released into the public domain - http://unlicense.org


readRawData and readFloatData are called by passing the pointers to the variables that you wish
to return the temperature and humidity values to. You will therefore need to assign these variables first.
You should also check that the function returned with 1 indicating a successful read e.g.
 
  #define DATAPIN 19 
  DHT mydht(DHT22,DATAPIN);
    
  float temperature;
  float humidity;
  if(mydht.readFloatData(&temperature, &humidity)){
    Serial.print("DHT11 Temp: ");
    Serial.print(temperature);
    Serial.print((char)176);                //Print degree symbol
    Serial.print("C, Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
  }
  
 For DHT11 which only returns integer values
  #define DATAPIN 19 
  DHT mydht(DHT11,DATAPIN); 
  
  int16_t temperature;
  int16_t humidity;
  if(mydht.readRawData(&temperature, &humidity)){
    Serial.print("DHT11 Temp: ");
    Serial.print(temperature);
    Serial.print((char)176);                //Print degree symbol
    Serial.print("C, Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
  }
*/

#ifndef DHT_H_
#define DHT_H_
#include "Energia.h"
#define DHT_TIMEOUT 250000
#define DATAPIN 19

#define DHT11 0
#define DHT22 1

class DHT
{
  private:
	uint8_t pin;
        uint8_t _device;


  public:
  DHT();
  DHT(uint8_t device);
  DHT(uint8_t device, uint8_t datapin);
  int8_t readRawData(int16_t *temperature, int16_t *humidity);    // Returns 1 if successful 0 otherwise  
  int8_t readFloatData(float *temperature, float *humidity);      // Returns 1 if successful 0 otherwise
  float convertTemperature(int16_t temperaure);
  float convertHumidity(int16_t humidity);  
};

#endif
