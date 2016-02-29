#include "Energia.h"

// Include application, user and local libraries

#include "rtosGlobals.h"
#include "Event.h"

void setup_serial()
{
  Serial.begin(115200);
  delay(500);
}


void loop_serial()
{
  myEvent.waitFor();
  Serial.println("Tap");
}

