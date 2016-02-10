// Include external libraries

#include <WiFi.h>


#define LED RED_LED

// Wireless network parameters
char ssid[] = "XXX";         // Your wireless network name also called SSID
char password[] = "XXX";       // Your wireless network password

char thingSpeakAddress[] = "api.thingspeak.com";
char talkBackAPIKey[] = "XXXX";
char talkBackID[] = "XXXX";

const unsigned long postingInterval = 15L * 1000L; // delay between updates, in milliseconds

char deviceId[] = "xxxxxxxxxxxx";

// Create MAC address and WiFiIPStack objects
MACAddress mac;
  
WiFiClient client; 

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
}

// Main loop. Runs continuously
void loop() {

 checkTalkBack();   
    
 delay(15000);
}

void checkTalkBack()
{
  char c;
  if (client.connect(thingSpeakAddress, 80)){
    Serial.println("Connected to thingspeak");
    client.print("GET /talkbacks/");
    client.print(talkBackID);
    client.print("/commands/execute?api_key=");
    client.print(talkBackAPIKey);
    client.print(" HTTP/1.1\r\n");
    client.print("Host: api.thingspeak.com\r\n");
    client.println("Connection: close\r\n");
    }

    Serial.println(F("Reading answer..."));
    String currentLine = "";
  while (client.connected()) {
    while (client.available()) {
      c = char(client.read());
      if (c == '\n'){
        Serial.println(currentLine);
        currentLine = "";
        } else if (c != '\r') {
          currentLine +=c;
        }
    }
  }
  client.stop();
  
  Serial.println(currentLine);
 
  if (currentLine == "TURN_ON")
  {  
    digitalWrite(LED, HIGH);
  }
  else if (currentLine == "TURN_OFF")
  {      
    digitalWrite(LED, LOW);
  }
}

