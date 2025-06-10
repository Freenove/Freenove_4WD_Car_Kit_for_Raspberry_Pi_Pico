/**********************************************************************
  Filename    : Infrared Remote Control
  Description : Decode the infrared remote control and print it out through the serial port.
  Auther      : www.freenove.com
  Modification: 2023/04/13
**********************************************************************/
#include <IRremote.hpp>
#define IR_Pin 3  // Infrared receiving pin
#define ENABLE_LED_FEEDBACK true
#define DISABLE_LED_FEEDBACK false
void setup() {
  Serial.begin(115200);                           // Initialize the serial port and set the baud rate to 115200
  IrReceiver.begin(IR_Pin, DISABLE_LED_FEEDBACK);  // Start the receiver
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(IR_Pin);  //print the infrared receiving pin
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long value = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(value, HEX);  // Print "old" raw data
    IrReceiver.resume();    // Enable receiving of the next value
  }
}
