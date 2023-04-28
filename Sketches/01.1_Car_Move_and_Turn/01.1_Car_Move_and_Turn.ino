/**********************************************************************
  Product     : Freenove 4WD Car for Raspberry Pi Pico (W)
  Auther      : www.freenove.com
  Modification: 2023/04/06
**********************************************************************/
#include "Freenove_4WD_Car_For_Pico_W.h"
void setup() {
  Servo_Setup();
  Motor_Setup();  //Motor Initializes
}

void loop() {
  Motor_Move(50, 50);  //go forward
  delay(1000);
  Motor_Move(0, 0);  //stop
  delay(1000);
  Motor_Move(-50, -50);  //go back
  delay(1000);
  Motor_Move(0, 0);  //stop
  delay(1000);
  Motor_Move(-50, 50);  //turn left
  delay(1000);
  Motor_Move(0, 0);  //stop
  delay(1000);
  Motor_Move(50, -50);  //turn right
  delay(1000);
  Motor_Move(0, 0);  //stop
  delay(1000);
}
