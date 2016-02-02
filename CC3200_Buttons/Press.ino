/* The event is triggered by the rising edge interrupt. The event debounces the button
and and indicates if the switch is pressed. While pressed the event continually polls the
pin state to detect when the switch is released.

Whilst the switch is pressed the event times the length of the press.

If a valid press is not detected or the switch is released the rising edge interrupt is
reenabled to detect the next button press and the event exits.
*/

// Include application, user and local libraries
#include "rtosGlobals.h"

long startPressTime;

void pressSetup()
{
  Serial.begin(115200);
  delay(50);
}


void pressLoop()
{
  pressEvent.waitFor();
  int count = DEBOUNCE_COUNT;
  int zeros = DEBOUNCE_COUNT;
  while (count && zeros) {
    int reading = digitalRead(PIN1);
    if (reading == HIGH) count--;
    else {
      count = DEBOUNCE_COUNT;
      zeros--;
    }
    delay(DEBOUNCE_DELAY);
  }
  if (!count){
    startPressTime = millis();
    //attachInterrupt(_pin1, release_int, FALLING); // Interrupt is fired whenever button is released
    
    //Put Pressed action here
     Serial.print("Pressed");
     while (digitalRead(PIN1)) delay(DEBOUNCE_DELAY);
     Serial.print(", Released after ");
     Serial.print(millis()-startPressTime);
     Serial.println(" ms");
     delay(50);  
  }
  attachInterrupt(PIN1, press_int, RISING); // Reenable the RISING edge interrupt to detect the next button press
}

