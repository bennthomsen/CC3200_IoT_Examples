#include "Energia.h"

// Include application, user and local libraries

#include "rtosGlobals.h"
#include "Event.h"

void serial_Setup()
{
  Serial.begin(115200);
  delay(500);
}


void serial_Loop()
{
  myEvent.waitFor();
  Serial.println("Tap");
}

