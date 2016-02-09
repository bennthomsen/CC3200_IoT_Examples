# TI CC3200 IoT Examples

##Buttons Example
This example shows how to use the TI RTOS in Energia to detect and debounce a button press. It makes use of the TI RTOS Event class

##CC3200 Sensors
This queries the Thermopile temperature sensor (TMP006) and Three axis accelerometer (BMA222) that are included on the CC3200 board and outputs the reading to a serial console.

##CC3200 ThinkSpeak Temp
An IoT Temperature sensing example using the TI CC3200 and the ThingSpeak IoT cloud service.

You will need to create a ThingSpeak Account at https://thingspeak.com
Follow the [instructions here](https://uk.mathworks.com/help/thingspeak/collect-data-in-a-new-channel.html) to create a new channel

The example code publishes to the following fields:
* field1 = deviceID
* field2 = Object Temperature
* field3 = Device Temperature
