/**********************************************************************
  Filename    : IR_Receiver_Car.ino
  Product     : Freenove 4WD Car for Raspberry Pi Pico (W)
  Auther      : www.freenove.com
  Modification: 2023/04/13
**********************************************************************/
#include <Arduino.h>
#include <IRremote.hpp>
#include "Freenove_4WD_Car_For_Pico_W.h"
#define IR_Pin 3
#define ENABLE_LED_FEEDBACK true
#define DISABLE_LED_FEEDBACK false
int motor_speed = 50;
int emotionMode = 4;
int motor_flag = 0;

void setup() {
  Serial.begin(115200);
  Motor_Setup();                                  //Motor initialization
  Emotion_Setup();                                //Initializes Emotion module
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
}

void handleControl(unsigned long value) {
  // Handle the commands
  switch (value) {
    case 0xBF40FF00:  // Receive the number '+'
      motor_flag = 1;
      Motor_Move(motor_speed , motor_speed);  // Go forward
      delay(200);
      Motor_Move(0 , 0);
      break;

    case 0xE619FF00:  // Receive the number '-'
      motor_flag = 2;
      Motor_Move(-motor_speed , -motor_speed);  // Back up
      delay(200);
      Motor_Move(0 , 0);
      break;

    case 0xF807FF00:  // Receive the number '|<<'
      motor_flag = 3;
      Motor_Move(-motor_speed , motor_speed);  // Turn left
      delay(200);
      Motor_Move(0 , 0);
      break;

    case 0xF609FF00:  // Receive the number '>>|'
      motor_flag = 4;
      Motor_Move(motor_speed , -motor_speed);  // Turn right
      delay(200);
      Motor_Move(0 , 0);
      break;

    case 0xE916FF00:  // Receive the number '0'
      emotionMode = millis() % 10;
      break;

    default:
      motor_flag = 0;
      Motor_Move(0 , 0);  //stop
      break;
  }
}
