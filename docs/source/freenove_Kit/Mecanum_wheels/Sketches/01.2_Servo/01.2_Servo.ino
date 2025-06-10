/**********************************************************************
  Product     : Freenove 4WD Car for Raspberry Pi Pico (W)
  Description : use servo.
  Auther      : www.freenove.com
  Modification: 2023/07/10
**********************************************************************/
#include "Freenove_4WD_Car_For_Pico_W.h"
void setup()
{
  Servo_Setup();       //Servo initialization
  Servo_1_Angle(90);   //Set servo 1 Angle
  delay(1000);
}

void loop()
{
  // Servo 1 motion path; 90°- 30°- 150°- 90°
   Servo_Sweep(1, 90, 30);
   Servo_Sweep(1, 30, 150);
   Servo_Sweep(1, 150, 90);
}
