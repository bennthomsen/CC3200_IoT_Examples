/*
 * This Sketch demonstrates the Event library and hardware interrupts to detect scahnges on input pins.
 Here the switch labelled SW3 on the CC3200 is used
 
 Benn Thomsen
 */

// Include application, user and local libraries
#include "rtosGlobals.h"

// Rising edge interrupt function
void press_int(){
  detachInterrupt(PIN1);
  pressEvent.send();
}

// The setup routine runs once when you press reset:
void setup()
{
  pinMode(RED_LED, OUTPUT);
  pinMode(PIN1,INPUT);
  attachInterrupt(PIN1, press_int, RISING); // Interrupt is fired whenever button is pressed
  pressEvent.begin();
}

// The loop routine runs over and over again forever:
void loop()
{
  // This is the main loop. In this example it does nothing as this example simple waits for a button press
}

