/**********************************************************************
  Filename    : IR_Receiver_Car.ino
  Product     : Freenove 4WD Car for Raspberry Pi Pico (W)
  Auther      : www.freenove.com
  Modification: 2023/04/13
**********************************************************************/
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <IRremote.hpp>
#include "Freenove_4WD_Car_For_Pico_W.h"
#include "Freenove_4WD_Car_Emotion.h"
#include "Freenove_VK16K33_Lib.h"
#include "Freenove_4WD_Car_WS2812.h"

#define IR_Pin 3  // Infrared receiving pin
#define ENABLE_LED_FEEDBACK          true
#define DISABLE_LED_FEEDBACK         false

static int servo_1_angle = 90;
int emotion_flag = 0;
int ws2812_flag = 0;

int CAR_MODE_VOL = 0;
int LASt_CAR_MODE_VOL = 0;

void setup() {
  Serial.begin(115200);  //Turn on the serial port monitor and set the baud rate to 115200
  Motor_Setup();         //Initialize motor
  Servo_Setup();         //Initialize servo
  Buzzer_Setup();        //Initialize the buzzer  
  WS2812_Setup();        //WS2812 initialization
  Emotion_and_Ultrasonic_Setup();
  IrReceiver.begin(IR_Pin, DISABLE_LED_FEEDBACK); // Start the receiver
  Servo_1_Angle(servo_1_angle);
  delay(100);
}

void loop() {
  if (IrReceiver.decode()) {
      unsigned long value=IrReceiver.decodedIRData.decodedRawData;
      handleControl(value);  // Handle the commands from remote control
      Serial.println(value, HEX); // Print "old" raw data
      Serial.println();
      IrReceiver.resume();  // Enable receiving of the next value
  }
  Emotion_and_Ultrasonic_Setup();
  oa_CalculateVoltageCompensation();
  if (Check_Module_value == MATRIX_IS_EXIST) {
    Emotion_Show(emotion_task_mode); //Led matrix display function
  } else if (Check_Module_value == SONAR_IS_ESIST) {
  }
  Car_Select(carFlag);
  WS2812_Show(ws2812_task_mode);    //Car color lights display function
}

void handleControl(unsigned long value) {
  // Handle the commands
  switch (value) {
    case 0xBF40FF00:  // Receive the number '+'
      Motor_Move(50, 50);
      delay(300);
      Motor_Move(0, 0);
      break;
    case 0xE619FF00:  // Receive the number '-'
      Motor_Move(-50, -50);
      delay(300);
      Motor_Move(0, 0);
      break;
    case 0xF807FF00:  // Receive the number '|<<'
      Motor_Move(-50, 50);
      delay(300);
      Motor_Move(0, 0);
      break;
    case 0xF609FF00:  // Receive the number '>>|'
      Motor_Move(50, -50);
      delay(300);
      Motor_Move(0, 0);
      break;
    case 0xEA15FF00:  // Receive the number '▶'
      Motor_Move(0, 0);
      break;
    case 0xE916FF00:  // Receive the number '0'
      servo_1_angle = servo_1_angle + 10;
      Servo_1_Angle(servo_1_angle);
      break;
    case 0xF30CFF00:  // Receive the number '1'
      servo_1_angle = servo_1_angle - 10;      
      Servo_1_Angle(servo_1_angle);
      break;
    case 0xF708FF00:  // Receive the number '4'
      servo_1_angle = 90;
      Servo_1_Angle(servo_1_angle);
      break;
    case 0xF20DFF00:  // Receive the number 'C'
      isLightModeFirstStarting = true; 
      Servo_1_Angle(90);
      Car_SetMode(1);
      break;
    case 0xA15EFF00:  // Receive the number '3'
      Servo_1_Angle(90);
      Car_SetMode(2);
      break;
    case 0xA55AFF00:  // Receive the number '6'
      Servo_1_Angle(90);
      if (Check_Module_value == SONAR_IS_ESIST) {
        LASt_CAR_MODE_VOL = 1;
        Car_SetMode(3);
      }
      if (Check_Module_value != SONAR_IS_ESIST) {
        Buzzer_Variable(2000, 50, 2);
        Car_SetMode(0);
        Motor_Move(0, 0);
      }
      break;
    case 0xB54AFF00:  // Receive the number '9'
      emotion_flag = 0;
      Emotion_SetMode(emotion_flag);    
      Servo_1_Angle(90);
      Car_SetMode(0);
      Motor_Move(0, 0);
      break;
    case 0xBB44FF00:  // Receive the number 'TEST'
      Buzzer_Variable(2000, 100, 1);
      break;
    case 0xE718FF00:  // Receive the number '2'
      if (Check_Module_value == MATRIX_IS_EXIST) {
        emotion_flag = emotion_flag + 1;
        if (emotion_flag > 7) {
          emotion_flag = 0;
        }
        Emotion_SetMode(emotion_flag);  //Display
        Serial.print(" \n matrix is exist !!! \n");
      }
      if (Check_Module_value != MATRIX_IS_EXIST) {
        Buzzer_Variable(2000, 50, 2);
        Serial.print(" \n sonar is exist !!! \n");
      }
      break;
    case 0xE31CFF00:  // Receive the number '5'
      emotion_flag = 0;
      Emotion_SetMode(emotion_flag);
      break;
    case 0xBD42FF00:  // Receive the number '7'
      ws2812_flag = ws2812_flag + 1;
      if (ws2812_flag >= 6) {
        ws2812_flag = 0;
      }
      WS2812_SetMode(ws2812_flag);
      break;
    case 0xAD52FF00:  // Receive the number '8'
      ws2812_flag = 0;
      WS2812_SetMode(ws2812_flag);
      break;
    case 0xFFFFFFFF:  // Remain unchanged
      break;
    default:
      break;
  }
}
