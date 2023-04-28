/**********************************************************************
  Filename    : Photosensitive_Car.ino
  Product     : Freenove 4WD Car for Raspberry Pi Pico (W)
  Auther      : www.freenove.com
  Modification: 2023/04/13
**********************************************************************/
#include <Arduino.h>
#include "Freenove_4WD_Car_For_Pico_W.h"

void setup() {
  Buzzer_Setup();
  Photosensitive_Setup();  //Photosensitive initialization
  Motor_Setup();           //Motor initialization
  Buzzer_Alert(1, 1);      //The buzzer beeps to prompt the user to start playing
  Serial.begin(115200);    //Initialize the serial port and set the baud rate to 115200
}

void loop() {
  Light_Car();
}
