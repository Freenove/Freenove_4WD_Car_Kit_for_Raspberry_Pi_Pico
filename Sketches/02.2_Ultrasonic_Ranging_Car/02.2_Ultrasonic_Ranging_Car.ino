/**********************************************************************
  Product     : Freenove 4WD Car for Raspberry Pi Pico (W)
  Description : Ultrasonic Car.
  Auther      : www.freenove.com
  Modification: 2023/04/13
**********************************************************************/
#include <Arduino.h>
#include "Freenove_4WD_Car_For_Pico_W.h"

void setup() {
  Ultrasonic_Setup();           //Initialize the ultrasonic module
  Motor_Setup();                //motor initialization
  Servo_Setup();                //servo initialization
}
void loop()
{
  Ultrasonic_Car();
}
