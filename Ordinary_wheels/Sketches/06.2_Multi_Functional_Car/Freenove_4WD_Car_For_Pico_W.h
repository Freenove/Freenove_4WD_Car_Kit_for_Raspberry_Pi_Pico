#ifndef _FREENOVE_4WD_CAR_H
#define _FREENOVE_4WD_CAR_H
#include <Arduino.h>
#include "RP2040_PWM.h"  

// #define REVERSE_MOTOR1
// #define REVERSE_MOTOR2
// #define REVERSE_MOTOR3
// #define REVERSE_MOTOR4

#define MATRIX_IS_EXIST 1
#define SONAR_IS_ESIST 2

// define car mode value
#define CAR_MODE_MANUAL 0
#define CAR_MODE_LIGHT_TRACING 1
#define CAR_MODE_LINE_TRACKING 2
#define CAR_MODE_SONAR 3

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
void Buzzer_Alarm(bool enable);          //Buzzer alarm function
void Buzzer_Variable(int frequency, int time, int times);

////////////////////Battery drive area/////////////////////////////////////
#define PIN_BATTERY        26        //Set the battery detection voltage pin
#define LOW_VOLTAGE_VALUE  525       //Set the minimum battery voltage
#define BAT_VOL_STANDARD	8.4
#define OA_SPEED_OFFSET_PER_V	3
extern int oa_VoltageCompensationToSpeed;

extern float batteryCoefficient;    //Set the proportional coefficient

int Get_Battery_Voltage_ADC(void);   //Gets the battery ADC value
float Get_Battery_Voltage(void);     //Get the battery voltage value
void Set_Battery_Coefficient(float coefficient);//Set the partial pressure coefficient
void oa_CalculateVoltageCompensation(void);

////////////////////Photosensitive drive area//////////////////////////////
#define Left_PHOTOSENSITIVE_PIN    28
#define Right_PHOTOSENSITIVE_PIN   27

void Photosensitive_Setup(void);           //Photosensitive initialization
int getLeftPhotosensitiveADCValue(void);              //Gets the photosensitive resistance value
int getRightPhotosensitiveADCValue(void);              //Gets the photosensitive resistance value
void Light_Car(void);               //Light Car

/////////////////////Ultrasonic drive area/////////////////////////////////
#define PIN_SONIC_TRIG    4            //define Trig pin 4 17 
#define PIN_SONIC_ECHO    5            //define Echo pin 5 22
#define MAX_DISTANCE      300           //cm
#define SONIC_TIMEOUT (MAX_DISTANCE*60) // calculate timeout 
#define SOUND_VELOCITY    340           //soundVelocity: 340m/s
void Ultrasonic_Setup(void);//Ultrasonic initialization
float Get_Sonar(void);//Obtain ultrasonic distance data
extern int sonar_distance; 

#define OBSTACLE_DISTANCE      45
#define OBSTACLE_DISTANCE_LOW  25

void get_distance(int car_mode);
void Ultrasonic_Car(void);

/////////////////////Track drive area//////////////////////////////
#define PIN_TRACKING_LEFT   12
#define PIN_TRACKING_CENTER 11
#define PIN_TRACKING_RIGHT  10
extern unsigned char sensorValue[4];
void Track_Setup(void);//Trace module initialization
void Track_Read(void);//Tracking module reading
void Track_Car(void);//Track Car

//////////////////////Car drive area////////////////////////////////////////
extern int carFlag;
void Car_SetMode(int mode);//set the car mode
void Car_Select(int mode);////select it to run car:0-command car，1-light car ，2-track car

extern int Check_Module_value;
extern bool isLightModeFirstStarting ;  //is_light_mode_first_starting

bool i2CAddrTest(uint8_t addr);
void Emotion_and_Ultrasonic_Setup(void);

void Get_Command(String inputStringTemp) ;

#endif
