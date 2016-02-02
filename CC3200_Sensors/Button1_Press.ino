void serialSetup()
{
}

void serialLoop()
{
  button1.waitForPress();
  Serial.println("Button was pressed!");
}
