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

//////////////////////Buzzer drive area///////////////////////////////////
//Buzzer pin definition             
#define PIN_BUZZER 2                    //Define the pins for the Pico W control buzzer
#define BUZZER_FREQUENCY 2000           //Define the resonant frequency of the buzzer 
void Buzzer_Setup(void);                //Buzzer initialization
void Buzzer_Alert(int beat, int rebeat);//Buzzer alarm function
void freq(int PIN, int freqs, int times); 

////////////////////Battery drive area/////////////////////////////////////
#define PIN_BATTERY        26        //Set the battery detection voltage pin
#define LOW_VOLTAGE_VALUE  525       //Set the minimum battery voltage
extern float batteryCoefficient;     //Set the proportional coefficient

int Get_Battery_Voltage_ADC(void);   //Gets the battery ADC value
float Get_Battery_Voltage(void);     //Get the battery voltage value
void Set_Battery_Coefficient(float coefficient);//Set the partial pressure coefficient

#endif
