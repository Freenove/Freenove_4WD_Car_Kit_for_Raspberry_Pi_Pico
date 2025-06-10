/**********************************************************************
  Filename    : IR_Receiver_Car.ino
  Product     : Freenove 4WD Car for Raspberry Pi Pico (W)
  Auther      : www.freenove.com
  Modification: 2023/07/10
**********************************************************************/
#include <Arduino.h>
#include <IRremote.hpp>
#include "Freenove_4WD_Car_For_Pico_W.h"
#define IR_Pin 3
#define ENABLE_LED_FEEDBACK true
#define DISABLE_LED_FEEDBACK false
int motor_speed = 50;
int emotionMode = 4;
float time_proportion = 5.7;  //If you want to get the best out of the rotation mode, change the value by experimenting
int motor_flag = 0;
int set_angle = 0;  //Set the forward angle of rotation
int rotate_flag = 0;
int around_rotate_flag = 0;
float battery_voltage = 0;

void setup() {
  Serial.begin(115200);
  Motor_Setup();                                   //Motor initialization
  Emotion_Setup();                                 //Initializes Emotion module
  IrReceiver.begin(IR_Pin, DISABLE_LED_FEEDBACK);  // Start the receiver
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long value = IrReceiver.decodedIRData.decodedRawData;
    handleControl(value);        // Handle the commands from remote control
    Serial.println(value, HEX);  // Print "old" raw data
    Serial.println();
    IrReceiver.resume();  // Enable receiving of the next value
  }
  showEmotion(emotionMode);
  if (rotate_flag) {  //Rotate when the rotate_glag is true
    int VY = 40 * cos(set_angle * (M_PI / 180));
    int VX = -(40 * sin(set_angle * (M_PI / 180)));
    int W = 40;

    int FR = VY - VX + W;
    int FL = VY + VX - W;
    int BL = VY - VX - W;
    int BR = VY + VX + W;

    Motor_M_Move(FL, BL, BR, FR);
    delay(5 * time_proportion * 8 / battery_voltage);
    set_angle -= 5;
  }
  //The car rotates around a point
  if (around_rotate_flag) {                     //Rotate when the rotate_glag is true 围绕旋转模式//-90 100 90 100
    int LY = 100 * cos(-90 * (M_PI / 180));     //paramters[1] represents the Angle to the the Y-axis,Counterclockwise is 0 to 180 degrees
    int LX = -(100 * sin(-90 * (M_PI / 180)));  //paramters[2] represents the move speed(the first jostick)
    int RX = 100 * sin(90 * (M_PI / 180));      //paramters[3] represents the Angle to the Y-axis,Counterclockwise is 0 to 180 degrees
    int RY = 100 * cos(90 * (M_PI / 180));      //Converts data from the client to its x and y axis positions
    int FR = LY - LX + RX;  //The McNamum wheel chassis motion formula
    int FL = LY + LX - RX;  //LY stands for longitudinal velocity
    int BL = LY - LX - RX;  //LX stands for transverse velocity
    int BR = LY + LX + RX;  //RX stands for angular velocity
    Motor_M_Move(FL, BL, BR, FR);
  }
}

void handleControl(unsigned long value) {
  // Handle the commands
  switch (value) {
    case 0xBF40FF00:  // Receive the number '+'
      rotate_flag = 0;
      Motor_M_Move(motor_speed, motor_speed, motor_speed, motor_speed);  // Go forward
      delay(500);
      Motor_M_Move(0, 0, 0, 0);
      break;

    case 0xE619FF00:  // Receive the number '-'
      rotate_flag = 0;
      Motor_M_Move(-motor_speed, -motor_speed, -motor_speed, -motor_speed);  // Back up
      delay(500);
      Motor_M_Move(0, 0, 0, 0);
      break;

    case 0xF807FF00:  // Receive the number '|<<'
      rotate_flag = 0;
      if (!motor_flag) {
        Motor_M_Move(-motor_speed, -motor_speed, motor_speed, motor_speed);  // Turn left
        delay(200);
        Motor_M_Move(0, 0, 0, 0);
        break;
      } else {
        Motor_M_Move(-motor_speed, motor_speed, -motor_speed, motor_speed);  // Turn left
        delay(500);
        Motor_M_Move(0, 0, 0, 0);
        break;
      }
    case 0xF609FF00:  // Receive the number '>>|'
      rotate_flag = 0;
      if (!motor_flag) {
        Motor_M_Move(motor_speed, motor_speed, -motor_speed, -motor_speed);  // Turn right
        delay(200);
        Motor_M_Move(0, 0, 0, 0);
        break;
      } else {
        Motor_M_Move(motor_speed, -motor_speed, motor_speed, -motor_speed);  // Turn right
        delay(500);
        Motor_M_Move(0, 0, 0, 0);
        break;
      }
    case 0xBB44FF00:  //Receive the number 'TEST'
      rotate_flag = 0;
      if (motor_flag) {
        Motor_M_Move(0, motor_speed, 0, motor_speed);  // Move forward and to the left diagonally
        delay(500);
        Motor_M_Move(0, 0, 0, 0);
        break;
      } else {
        break;
      }

    case 0xF20DFF00:  //Receive the number 'c'
      rotate_flag = 0;
      if (motor_flag) {
        Motor_M_Move(0, -motor_speed, 0, -motor_speed);  // Move backward and to the right diagonally
        delay(500);
        Motor_M_Move(0, 0, 0, 0);
        break;
      } else {
        break;
      }

    case 0xBC43FF00:  //Receive the number '↗'
      rotate_flag = 0;
      if (motor_flag) {
        Motor_M_Move(motor_speed, 0, motor_speed, 0);  // Move forward and to the right diagonally
        delay(500);
        Motor_M_Move(0, 0, 0, 0);
        break;
      } else {
        break;
      }

    case 0xE916FF00:  //Receive the number '0'
      rotate_flag = 0;
      if (motor_flag) {
        Motor_M_Move(-motor_speed, 0, -motor_speed, 0);  // Move back and to the left diagonally
        delay(500);
        Motor_M_Move(0, 0, 0, 0);
        break;
      } else {
        break;
      }

    case 0xF30CFF00:  // Receive the number '1'
      emotionMode = millis() % 10;
      break;

    case 0xEA15FF00:  // Receive the number '▶'
      rotate_flag = 0;
      motor_flag = !motor_flag;
      break;

    case 0xB847FF00:  // Receive the number 'MENU'
      battery_voltage = Get_Battery_Voltage();
      rotate_flag = !rotate_flag;
      set_angle = 0;
      break;

    case 0xE718FF00:  // Receive the number '2'
      around_rotate_flag = !around_rotate_flag;
      break;

    default:
      Motor_M_Move(0, 0, 0, 0);  //stop
      break;
  }
}
