// Include external libraries
#include <SPI.h>
#include <WiFi.h>
//Required for BMA222 Accelerometer sensor
#include <BMA222.h>
//Required for TMP006 Temperature sensor
#include <Wire.h>
#include "Adafruit_TMP006.h"

// Wireless network parameters
char ssid[] = "YourSSID";          // Your wireless network name also called SSID
char password[] = "YourWifiPassword";       // Your wireless network password

char thingSpeakAddress[] = "api.thingspeak.com";
char apiKey[] = "YourThinkSpeakWriteAPIKey";

const unsigned long postingInterval = 15L * 1000L; // delay between updates, in milliseconds

#define POSTSTRING "field1=%s&field2=%5.2f&field3=%5.2f"

//Initialise dataString char Array
char dataString[]="field1=5c313e0555cf&field2=00.00&field3=00.00";
char deviceId[] = "xxxxxxxxxxxx";

// Create MAC address and WiFiIPStack objects
MACAddress mac;
  
WiFiClient client; 

// Define external sensors, inputs and outputs.
BMA222 accSensor;            // Three axis acceleration sensor
Adafruit_TMP006 tmp006(0x41);

// Setup function runs once when microprocessor is powered up
void setup() {
  uint8_t macOctets[6]; 
  Serial.begin(115200);          //Initialise serial port for local monitoring on the Serail Monitor via USB
  Serial.print("Attempting to connect to Network named: ");
  Serial.println(ssid);
  
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    Serial.print(".");         // print dots while we wait to connect
    delay(300);
  }
  
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");
  
  while (WiFi.localIP() == INADDR_NONE) {
    Serial.print(".");        // print dots while we wait for an ip addresss
    delay(300);
  }

  // We are connected and have an IP address.
  Serial.print("\nIP Address obtained: ");
  Serial.println(WiFi.localIP());

  mac = WiFi.macAddress(macOctets);
  Serial.print("MAC Address: ");
  Serial.println(mac);
  
  // Use MAC Address as deviceId
  sprintf(deviceId, "%02x%02x%02x%02x%02x%02x", macOctets[0], macOctets[1], macOctets[2], macOctets[3], macOctets[4], macOctets[5]);
  Serial.print("deviceId: ");
  Serial.println(deviceId);

  if (!tmp006.begin()) {
    Serial.println("No sensor found");
    while (1);
  }
  
  // start the accel sensor
  accSensor.begin();
  uint8_t chipID = accSensor.chipID();
  Serial.print("ChipID: ");
  Serial.println(chipID);
}

// Main loop. Runs continuously
void loop() {
    Serial.println("Preparing to post");
    if (client.connect(thingSpeakAddress,80)){
      Serial.println("Connected to server");
      sprintf(dataString,POSTSTRING,deviceId,tmp006.readObjTempC(),tmp006.readDieTempC());
      //Other sensor/data sources
      // accSensor.readXData(), accSensor.readYData(),accSensor.readZData(),-WiFi.RSSI()
      Serial.print("Posting: ");
      Serial.println(dataString);
      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("X-THINGSPEAKAPIKEY: ");
      client.print(apiKey);
      client.print("\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(sizeof(dataString)-1);
      client.print("\n\n");
      client.print(dataString);
      client.stop();
    }
    else {
      // if you couldn't make a connection:
      Serial.println("connection failed");
    }
 delay(postingInterval);
}


