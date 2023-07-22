/**********************************************************************
  Product     : Freenove 4WD Car for Raspberry Pi Pico (W)
  Description : Set the Angle value of servo to 90°
  Auther      : www.freenove.com
  Modification: 2023/07/10
**********************************************************************/
#include "Freenove_4WD_Car_For_Pico_W.h"

void setup() {
  Servo_Setup();  //Servo initialization
}

void loop() {
  Servo_1_Angle(90);  //Set the Angle value of servo 1 to 90°
  delay(1000);
}
