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

#include "DHT.h"
DHT::DHT() {
  pin = DATAPIN;
  _device = DHT11;
}

DHT::DHT(uint8_t device) {
  pin = DATAPIN;
  _device = device;
}

DHT::DHT(uint8_t device, uint8_t datapin) {
  pin = datapin;
  _device = device;
}

int8_t DHT::readRawData(int16_t *temperature, int16_t *humidity) {
	uint8_t bits[5];
	uint8_t i,j = 0;

	memset(bits, 0, sizeof(bits));

	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	if (_device)
	  delayMicroseconds(500);
        else
  	  delay(18);

	pinMode(pin, INPUT);
	digitalWrite(pin, HIGH);
	delayMicroseconds(40);

	//check start condition 1
	if(digitalRead(pin)==HIGH) {
		return -1;
	}
	delayMicroseconds(80);
	//check start condition 2
	if(digitalRead(pin)==LOW) {
		return -2;
	}
  
        //Sensor init ok, now read 5 bytes ...
        for (j=0; j<5; j++)
        {
          for (int8_t i=7; i>=0; i--)
          {
            if (pulseIn(pin, HIGH, 1000) > 30)
              bitSet(bits[j], i);
          }
        }
        
	//reset port
	pinMode(pin, INPUT);        

	if ((uint8_t)(bits[0] + bits[1] + bits[2] + bits[3]) == bits[4]) {
		//return temperature and humidity
                if (_device) {
		  *humidity = bits[0]<<8 | bits[1];
                  *temperature = bits[2]<<8 | bits[3];
                } else {
		  *humidity = bits[0];
                  *temperature = bits[2];
                }
		return 1;
	}

	return 0;
}

int8_t DHT::readFloatData(float *temperature, float *humidity)
{
  int16_t rawtemperature, rawhumidity;
  int8_t res = readRawData(&rawtemperature, &rawhumidity);
  if (res == 0)
  {
    return res;
  }
  if (_device) {
    *temperature = convertTemperature(rawtemperature);
    *humidity = convertHumidity(rawhumidity);
  } else {
    *temperature = (float)rawtemperature;
    *humidity = (float)rawhumidity;
  }
  return 1;
}

//dht22 only, since dht11 does not have decimals
float DHT::convertTemperature(int16_t rawtemperature)
{
  if(rawtemperature & 0x8000) {
    return (float)((rawtemperature & 0x7FFF) / 10.0) * -1.0;
  } else {
    return (float)rawtemperature/10.0;
  }
}

float DHT::convertHumidity(int16_t rawhumidity)
{
  return (float)rawhumidity/10.0;
}
