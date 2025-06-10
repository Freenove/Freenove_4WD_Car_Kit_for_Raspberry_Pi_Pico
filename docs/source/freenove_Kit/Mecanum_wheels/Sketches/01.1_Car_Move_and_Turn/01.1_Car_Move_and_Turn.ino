/**********************************************************************
  Product     : Freenove 4WD Car for Raspberry Pi Pico (W)
  Auther      : www.freenove.com
  Modification: 2023/07/10
**********************************************************************/
#include "Freenove_4WD_Car_For_Pico_W.h"

void setup() {
  Serial.begin(9600);
  Servo_Setup();
  Motor_Setup();  //Motor Initializes
}

void loop() {
  Motor_M_Move(50, 50, 50, 50);  //Farward
  delay(1000);
  Motor_M_Move(0, 0, 0, 0);  //Stop
  delay(1000);
  Motor_M_Move(-50, -50, -50, -50);  //Backward
  delay(1000);
  Motor_M_Move(0, 0, 0, 0);  //Stop
  delay(1000);
  Motor_M_Move(-50, -50, 50, 50);  //Turn left
  delay(1000);
  Motor_M_Move(0, 0, 0, 0);  //Stop
  delay(1000);
  Motor_M_Move(50, 50, -50, -50);  //Turn right
  delay(1000);
  Motor_M_Move(0, 0, 0, 0);  //Stop
  delay(1000);
  Motor_M_Move(-50, 50, -50, 50);  //Move left
  delay(1000);
  Motor_M_Move(0, 0, 0, 0);  //Stop
  delay(1000);
  Motor_M_Move(50, -50, 50, -50);  //Move right
  delay(1000);
  Motor_M_Move(0, 0, 0, 0);  //Stop
  delay(1000);
  Motor_M_Move(-50, 50, -50, 50);  //Move diagonally upward to the left
  delay(1000);
  Motor_M_Move(0, 0, 0, 0);  //Stop
  delay(1000);
  Motor_M_Move(0, -50, 0, -50);  //Move diagonally downward to the right
  delay(1000);
  Motor_M_Move(0, 0, 0, 0);  //Stop
  delay(1000);
  Motor_M_Move(50, 0, 50, 0);  //Move diagonally upward to the right
  delay(1000);
  Motor_M_Move(0, 0, 0, 0);  //Stop
  delay(1000);
  Motor_M_Move(-50, 0, -50, 0);  //Move diagonally downward to the left
  delay(1000);
  Motor_M_Move(0, 0, 0, 0);  //Stop
  delay(1000);
}
