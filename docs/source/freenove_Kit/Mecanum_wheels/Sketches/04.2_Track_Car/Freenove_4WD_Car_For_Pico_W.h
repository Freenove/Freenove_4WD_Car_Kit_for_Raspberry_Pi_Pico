#ifndef _FREENOVE_4WD_CAR_H
#define _FREENOVE_4WD_CAR_H

#include <Arduino.h>
#include "RP2040_PWM.h"  

// #define REVERSE_MOTOR1
// #define REVERSE_MOTOR2
// #define REVERSE_MOTOR3
// #define REVERSE_MOTOR4

/////////////////////Servo drive area///////////////////////////////////
#define PIN_SERVO1  13    //define servo pin

extern int servo_1_offset;                      //Define the offset variable for servo 1

void Servo_Setup(void);                         //servo initialization
void Servo_1_Angle(float angle);                //Set the rotation parameters of servo 1, and the parameters are 30-150 degrees
void Set_Servo_1_Offset(int offset);            //Set servo 1 offset
void Servo_Sweep(int servo_id, int angle_start, int angle_end);//Servo sweep function;

/////////////////////Motor drive area///////////////////////////////////
#define PIN_MOTOR_PWM_RIGHT1  7          //Define the positive pole of M3
#define PIN_MOTOR_PWM_RIGHT2  6          //Define the positive pole of M3
#define PIN_MOTOR_PWM_RIGHT3  9          //Define the negative pole of M4
#define PIN_MOTOR_PWM_RIGHT4  8          //Define the negative pole of M4
#define PIN_MOTOR_PWM_LEFT1   18         //Define the positive pole of M1
#define PIN_MOTOR_PWM_LEFT2   19         //Define the negative pole of M1
#define PIN_MOTOR_PWM_LEFT3   21         //Define the positive pole of M2
#define PIN_MOTOR_PWM_LEFT4   20         //Define the negative pole of M2
#define MOTOR_SPEED_MIN       -100       //Define a minimum speed limit for wheels
#define MOTOR_SPEED_MAX       100        //Define a maximum speed limit for wheels

void Motor_Setup(void);                //motor initialization
void Motor_Move_Init(int m1_speed, int m2_speed, int m3_speed, int m4_speed);//A function to control the car motor
void Motor_Move(int Left_speed, int Right_speed);//A function to control the car motor
void Motor_M_Move(int M1_speed, int M2_speed, int M3_speed,int M4_speed);//A function to control the maicanum wheel car motor

//////////////////////Buzzer drive area///////////////////////////////////
//Buzzer pin definition             
#define PIN_BUZZER 2                    //Define the pins for the Pico control buzzer
#define BUZZER_FREQUENCY 2000           //Define the resonant frequency of the buzzer 
void Buzzer_Setup(void);                //Buzzer initialization
void Buzzer_Alert(int beat, int rebeat);//Buzzer alarm function
void freq(int PIN, int freqs, int times); 

////////////////////Battery drive area/////////////////////////////////////
#define PIN_BATTERY        26        //Set the battery detection voltage pin
#define LOW_VOLTAGE_VALUE  525      //Set the minimum battery voltage
extern float batteryCoefficient;    //Set the proportional coefficient

int Get_Battery_Voltage_ADC(void);   //Gets the battery ADC value
float Get_Battery_Voltage(void);     //Get the battery voltage value
void Set_Battery_Coefficient(float coefficient);//Set the partial pressure coefficient

////////////////////Photosensitive drive area//////////////////////////////
#define PHOTOSENSITIVE_PIN   27
void Photosensitive_Setup(void);           //Photosensitive initialization
int Get_Photosensitive(void);              //Gets the photosensitive resistance value

/////////////////////Ultrasonic drive area/////////////////////////////////
#define PIN_SONIC_TRIG    4            //define Trig pin
#define PIN_SONIC_ECHO    5            //define Echo pin
#define MAX_DISTANCE      300           //cm
#define SONIC_TIMEOUT (MAX_DISTANCE*60) // calculate timeout 
#define SOUND_VELOCITY    340           //soundVelocity: 340m/s
void Ultrasonic_Setup(void);//Ultrasonic initialization
float Get_Sonar(void);//Obtain ultrasonic distance data

/////////////////////Track drive area//////////////////////////////
#define PIN_TRACKING_LEFT   12
#define PIN_TRACKING_CENTER 11
#define PIN_TRACKING_RIGHT  10
extern unsigned char sensorValue[4];
void Track_Setup(void);//Trace module initialization
void Track_Read(void);//Tracking module reading

//////////////////////Emotion drive area////////////////////////////////
#define EMOTION_ADDRESS 0x71
#define EMOTION_SDA     4
#define EMOTION_SCL     5
void Emotion_Setup();                            //Initialize
void eyesRotate(int delay_ms);                   //Turn the eyes-1
void eyesBlink(int delay_ms);                    //Wink the eyes-2
void eyesSmile(int delay_ms);                    //Smile-3
void eyesCry(int delay_ms);                      //Cry-4
void eyesBlink1(int delay_ms);                   //Wink the eyes-5
void showArrow(int arrow_direction,int delay_ms);//Arrow-6
void wheel(int mode,int delay_ms);               //wheel-7
void carMove(int mode,int delay_ms);             //car-8
void expressingLove(void);                       //expressing love-9
void saveWater(int delay_ms);                    //save water-10

#endif
