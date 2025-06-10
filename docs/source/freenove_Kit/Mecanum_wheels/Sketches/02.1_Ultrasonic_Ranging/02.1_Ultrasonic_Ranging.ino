/**********************************************************************
  Product     : Freenove 4WD Car for Raspberry Pi Pico (W)
  Description : Ultrasonic ranging and servo.
  Auther      : www.freenove.com
  Modification: 2023/04/13
**********************************************************************/
#include <Arduino.h>
#include "Freenove_4WD_Car_For_Pico_W.h"

void setup() {
  Serial.begin(115200);//Open the serial port and set the baud rate to 115200
  Ultrasonic_Setup();  //Ultrasonic module initialization
  Servo_Setup();       //Servo motor initialization
  Servo_1_Angle(90);   //Set the initial value of Servo 1 to 90 degrees
  delay(500);          //Wait for the servo to arrive at the specified location
}

void loop() {
  Servo_1_Angle(150);  //Turn servo 1 to 150 degrees
  Serial.print("Distance: " + String(Get_Sonar()) + "\n");//Print ultrasonic distance
  delay(500);

  Servo_1_Angle(90);   //Turn servo 1 to 90 degrees
  Serial.print("Distance: " + String(Get_Sonar()) + "\n");//Print ultrasonic distance
  delay(500);

  Servo_1_Angle(30);   //Turn servo 1 to 30 degrees
  Serial.print("Distance: " + String(Get_Sonar()) + "\n");//Print ultrasonic distance
  delay(500);

  Servo_1_Angle(90);   //Turn servo 1 to 90 degrees
  Serial.print("Distance: " + String(Get_Sonar()) + "\n");//Print ultrasonic distance
  delay(500);
}
