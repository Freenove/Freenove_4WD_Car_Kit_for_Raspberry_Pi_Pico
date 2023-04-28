#include <Arduino.h>
#include <Wire.h>
//#include "Adafruit_NeoPixel.h"
//#include "Freenove_4WD_Car_WiFi.h"
#include "Freenove_4WD_Car_Emotion.h"
#include "Freenove_4WD_Car_For_Pico_W.h"

/////////////////////Servo drive area///////////////////////////////////
uint32_t Servo_Pins[] = { PIN_SERVO1 };
#define NUM_OF_ServoPINS  ( sizeof(Servo_Pins) / sizeof(uint32_t) )
float dutyCycle1[NUM_OF_ServoPINS] = { 0.0f};
float freq1[] = { 50.0f};
RP2040_PWM* Servo_Instance[NUM_OF_ServoPINS];

int servo_1_offset=0; //Define the offset variable for servo 1

//servo initialization
void Servo_Setup(void)
{
  for (uint8_t index = 0; index < NUM_OF_ServoPINS; index++)
  {   
    Servo_Instance[index] = new RP2040_PWM(Servo_Pins[index], freq1[index], dutyCycle1[index]);
    if (Servo_Instance[index])
    {
      Servo_Instance[index]->setPWM();
      uint32_t div = Servo_Instance[index]->get_DIV();
      uint32_t top = Servo_Instance[index]->get_TOP();
      PWM_LOGDEBUG5("TOP =", top, ", DIV =", div, ", CPU_freq =", Servo_Instance[index]->get_freq_CPU());
    }
  }
}

//Set the rotation parameters of servo 1, and the parameters are 0-180 degrees
void Servo_1_Angle(float angle)
{
  angle = constrain(angle, 30, 150);
  angle=map(angle,0.0f,180.0f,2500.0f,12500.0f);
  Servo_Instance[0]->setPWM(PIN_SERVO1, 50.0f, angle/1000.0f);
}

//Set servo 1 offset
void Set_Servo_1_Offset(int offset)
{
  servo_1_offset=offset;
}

//Servo sweep function
void Servo_Sweep(int servo_id, int angle_start, int angle_end)
{
  if (servo_id == 1)
  {
    angle_start = constrain(angle_start, 0, 180);
    angle_end = constrain(angle_end, 0, 180);
  }
  if (angle_start > angle_end)
  {
    for (int i = angle_start; i >= angle_end; i--)
    {
      if (servo_id == 1)
        Servo_1_Angle(i);
      delay(10);
    }
  }
  if (angle_start < angle_end)
  {
    for (int i = angle_start; i <= angle_end; i++)
    {
      if (servo_id == 1)
        Servo_1_Angle(i);
      delay(10);
    }
  }
}

/////////////////////Motor drive area///////////////////////////////////
uint32_t PWM_Pins[] = { PIN_MOTOR_PWM_RIGHT1, PIN_MOTOR_PWM_RIGHT2, PIN_MOTOR_PWM_RIGHT3, PIN_MOTOR_PWM_RIGHT4, PIN_MOTOR_PWM_LEFT1, PIN_MOTOR_PWM_LEFT2, PIN_MOTOR_PWM_LEFT3, PIN_MOTOR_PWM_LEFT4 };
#define NUM_OF_PINS (sizeof(PWM_Pins) / sizeof(uint32_t))
float dutyCycle2[NUM_OF_PINS] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
float freq2[] = { 500.0f, 500.0f, 500.0f, 500.0f, 500.0f, 500.0f, 500.0f, 500.0f };
RP2040_PWM* PWM_Instance[NUM_OF_PINS];
//Motor initialization
void Motor_Setup(void) {
  for (uint8_t index = 0; index < NUM_OF_PINS; index++) {
    PWM_Instance[index] = new RP2040_PWM(PWM_Pins[index], freq2[index], dutyCycle2[index]);
    if (PWM_Instance[index]) {
      PWM_Instance[index]->setPWM();
      uint32_t div = PWM_Instance[index]->get_DIV();
      uint32_t top = PWM_Instance[index]->get_TOP();
      PWM_LOGDEBUG5("TOP =", top, ", DIV =", div, ", CPU_freq =", PWM_Instance[index]->get_freq_CPU());
    }
  }
}

//A function to control the car motor
void Motor_Move_Init(int m1_speed, int m2_speed, int m3_speed, int m4_speed) {
  float frequency = 500;
  m1_speed = constrain(m1_speed, MOTOR_SPEED_MIN, MOTOR_SPEED_MAX);
  m2_speed = constrain(m2_speed, MOTOR_SPEED_MIN, MOTOR_SPEED_MAX);
  m3_speed = constrain(m3_speed, MOTOR_SPEED_MIN, MOTOR_SPEED_MAX);
  m4_speed = constrain(m4_speed, MOTOR_SPEED_MIN, MOTOR_SPEED_MAX);
  if (m1_speed >= 0) {
    PWM_Instance[0]->setPWM(PIN_MOTOR_PWM_LEFT1, frequency, m1_speed);
    PWM_Instance[1]->setPWM(PIN_MOTOR_PWM_LEFT2, frequency, 0);
  } else {
    m1_speed = -m1_speed;
    PWM_Instance[1]->setPWM(PIN_MOTOR_PWM_LEFT2, frequency, m1_speed);
    PWM_Instance[0]->setPWM(PIN_MOTOR_PWM_LEFT1, frequency, 0);
  }
  if (m2_speed >= 0) {
    PWM_Instance[2]->setPWM(PIN_MOTOR_PWM_LEFT3, frequency, m2_speed);
    PWM_Instance[3]->setPWM(PIN_MOTOR_PWM_LEFT4, frequency, 0);
  } else {
    m2_speed = -m2_speed;
    PWM_Instance[3]->setPWM(PIN_MOTOR_PWM_LEFT4, frequency, m2_speed);
    PWM_Instance[2]->setPWM(PIN_MOTOR_PWM_LEFT3, frequency, 0);
  }
  if (m3_speed >= 0) {
    PWM_Instance[4]->setPWM(PIN_MOTOR_PWM_RIGHT1, frequency, m3_speed);
    PWM_Instance[5]->setPWM(PIN_MOTOR_PWM_RIGHT2, frequency, 0);
  } else {
    m3_speed = -m3_speed;
    PWM_Instance[5]->setPWM(PIN_MOTOR_PWM_RIGHT2, frequency, m3_speed);
    PWM_Instance[4]->setPWM(PIN_MOTOR_PWM_RIGHT1, frequency, 0);
  }
  if (m4_speed >= 0) {
    PWM_Instance[6]->setPWM(PIN_MOTOR_PWM_RIGHT3, frequency, m4_speed);
    PWM_Instance[7]->setPWM(PIN_MOTOR_PWM_RIGHT4, frequency, 0);
  } else {
    m4_speed = -m4_speed;
    PWM_Instance[7]->setPWM(PIN_MOTOR_PWM_RIGHT4, frequency, m4_speed);
    PWM_Instance[6]->setPWM(PIN_MOTOR_PWM_RIGHT3, frequency, 0);
  }
}
void Motor_Move(int Left_speed, int Right_speed) {
  int lf, lb, rf, rb;
  lf = lb = Left_speed;
  rf = rb = Right_speed;
#ifdef REVERSE_MOTOR1
  lf = -Left_speed;
#endif
#ifdef REVERSE_MOTOR2
  lb = -Left_speed;
#endif
#ifdef REVERSE_MOTOR3
  rf = -Right_speed;
#endif
#ifdef REVERSE_MOTOR4
  rb = -Right_speed;
#endif
  Motor_Move_Init(lf, lb, rf, rb);
}
//////////////////////Buzzer drive area///////////////////////////////////
void Buzzer_Setup(void) {
  pinMode(PIN_BUZZER, OUTPUT);
}

void Buzzer_Variable(int frequency, int time, int times) {
  for (int i = 0; i < times; i++) {
    tone(2, frequency);
    delay(time);
    tone(2, 0);
    delay(time);
  }
}

void Buzzer_Alarm(bool enable) {
  if (enable == 1) {
    freq(PIN_BUZZER, 2000, 30);
    delay(500);
    freq(PIN_BUZZER, 0, 30);
    delay(500);
  } else
    freq(PIN_BUZZER, 0, 30);
}

//Buzzer alarm function
void Buzzer_Alert(int beat, int rebeat) {
  beat = constrain(beat, 1, 9);
  rebeat = constrain(rebeat, 1, 255);
  for (int j = 0; j < rebeat; j++) {
    for (int i = 0; i < beat; i++) {
      freq(PIN_BUZZER, BUZZER_FREQUENCY, 10);
    }
    delay(500);
  }
  freq(PIN_BUZZER, 0, 10);
}

void freq(int PIN, int freqs, int times) {
  if (freqs == 0) {
    digitalWrite(PIN, LOW);
  } else {
    for (int i = 0; i < times * freqs / 500; i++) {
      digitalWrite(PIN, HIGH);
      delayMicroseconds(500000 / freqs);
      digitalWrite(PIN, LOW);
      delayMicroseconds(500000 / freqs);
    }
  }
}

////////////////////Battery drive area/////////////////////////////////////
float batteryVoltage = 0;      //Battery voltage variable
float batteryCoefficient = 4;  //Set the proportional coefficient
int oa_VoltageCompensationToSpeed;

//Gets the battery ADC value
int Get_Battery_Voltage_ADC(void) {
  pinMode(PIN_BATTERY, INPUT);
  int batteryADC = 0;
  for (int i = 0; i < 5; i++)
    batteryADC += analogRead(PIN_BATTERY);
  return batteryADC / 5;
}

//Get the battery voltage value
float Get_Battery_Voltage(void) {
  int batteryADC = Get_Battery_Voltage_ADC();
  batteryVoltage = (batteryADC / 1023.0 * 3.3) * batteryCoefficient;
  return batteryVoltage;
}

void oa_CalculateVoltageCompensation() {
  Get_Battery_Voltage();
  float voltageOffset = BAT_VOL_STANDARD - batteryVoltage;
  oa_VoltageCompensationToSpeed = voltageOffset * OA_SPEED_OFFSET_PER_V;
  // Serial.print(batteryVoltage);
	// Serial.print('\t');
  // Serial.print(voltageOffset);
	// Serial.print('\t');
	// Serial.println(oa_VoltageCompensationToSpeed);
}

void Set_Battery_Coefficient(float coefficient) {
  batteryCoefficient = coefficient;
}

/////////////////////Photosensitive drive area//////////////////////////
int light_init_value = 0;  //Set the car's initial environment ADC value
//Photosensitive initialization
void Photosensitive_Setup(void) {
  pinMode(Left_PHOTOSENSITIVE_PIN, INPUT);
  pinMode(Right_PHOTOSENSITIVE_PIN, INPUT);
}

//Gets the photosensitive resistance value
int getLeftPhotosensitiveADCValue(void) {
  int photosensitiveADCValue = analogRead(Left_PHOTOSENSITIVE_PIN);
  return photosensitiveADCValue;
}
//Gets the photosensitive resistance value
int getRightPhotosensitiveADCValue(void) {
  int photosensitiveADCValue = analogRead(Right_PHOTOSENSITIVE_PIN);
  return photosensitiveADCValue;
}

#define LIGHT_MIN_MOVED (50+oa_VoltageCompensationToSpeed)
#define LIGHT_MODE_CRUISE_SPEED (25+oa_VoltageCompensationToSpeed)     //0-100
bool isLightModeFirstStarting = true;  //is_light_mode_first_starting
//Light Car
void Light_Car() {
    if (isLightModeFirstStarting) {
      isLightModeFirstStarting = false;
      Motor_Move(40, 40);
      delay(200);
    }
    int leftLightValue = getLeftPhotosensitiveADCValue();
    int rightLightValue = getRightPhotosensitiveADCValue();
    int diffLightValue = (leftLightValue - rightLightValue) / 8;
    if (leftLightValue > LIGHT_MIN_MOVED && rightLightValue > LIGHT_MIN_MOVED) {
      int lsp = constrain(LIGHT_MODE_CRUISE_SPEED + diffLightValue, -100, 100);
      int rsp = constrain(LIGHT_MODE_CRUISE_SPEED - diffLightValue, -100, 100);
      // Serial.println("sp: " + String(lsp) + " " + String(rsp) + " " + String(diffLightValue));
      Motor_Move(lsp, rsp);
    } else {
      Motor_Move(0, 0);
    }
}

/////////////////////Ultrasonic drive area//////////////////////////////
//Ultrasonic initialization
void Ultrasonic_Setup(void) {
  pinMode(PIN_SONIC_TRIG, OUTPUT);  // set trigPin to output mode
  pinMode(PIN_SONIC_ECHO, INPUT);   // set echoPin to input mode
}

//Obtain ultrasonic distance data
float Get_Sonar(void) {
  unsigned long pingTime;
  float distance;
  digitalWrite(PIN_SONIC_TRIG, HIGH);  // make trigPin output high level lasting for 10μs to triger HC_SR04,
  delayMicroseconds(10);
  digitalWrite(PIN_SONIC_TRIG, LOW);
  pingTime = pulseIn(PIN_SONIC_ECHO, HIGH, SONIC_TIMEOUT);  // Wait HC-SR04 returning to the high level and measure out this waitting time
  if (pingTime != 0)
    distance = (float)pingTime * SOUND_VELOCITY / 2 / 10000;  // calculate the distance according to the time
  else
    distance = MAX_DISTANCE;
  // Serial.print("Distance: " + String(distance) + "\n");  //Print ultrasonic distance
  return distance;                                       // return the distance value
}

/////////////////////Track drive area//////////////////////////////
#define SPEED_LV4 (80+oa_VoltageCompensationToSpeed)
#define SPEED_LV3 (70+oa_VoltageCompensationToSpeed)
#define SPEED_LV2 (60+oa_VoltageCompensationToSpeed)
#define SPEED_LV1 (45+oa_VoltageCompensationToSpeed)
unsigned char sensorValue[4];  //define an array

//Trace module initialization
void Track_Setup(void) {
  pinMode(PIN_TRACKING_LEFT, INPUT);    //
  pinMode(PIN_TRACKING_RIGHT, INPUT);   //
  pinMode(PIN_TRACKING_CENTER, INPUT);  //
}

//Tracking module reading
void Track_Read(void) {
  sensorValue[0] = digitalRead(PIN_TRACKING_LEFT);
  sensorValue[1] = digitalRead(PIN_TRACKING_CENTER);
  sensorValue[2] = digitalRead(PIN_TRACKING_RIGHT);
  sensorValue[3] = sensorValue[0] << 2 | sensorValue[1] << 1 | sensorValue[2];
}

//Track Car
void Track_Car() {
    Track_Read();
    switch (sensorValue[3]) {  //white : 0  light , black: 1 ,
      case 2:                  //010
      case 5:
        Emotion_SetMode(3);
        Motor_Move(SPEED_LV1, SPEED_LV1);  //Move Forward
        break;
      case 0:              //000
        Motor_Move(0, 0);  //Stop
        break;
      case 7:  //111
        Emotion_SetMode(4);
        Motor_Move(SPEED_LV1, SPEED_LV1);  //Move Forward
        break;
      case 1:                               //001
      case 3:                               //011
        Emotion_SetMode(5);                 //Left
        Motor_Move(SPEED_LV3, -SPEED_LV4);  //Turn Right
        break;
      case 4:                               //100
      case 6:                               //110
        Emotion_SetMode(6);                 //Right
        Motor_Move(-SPEED_LV4, SPEED_LV3);  //Turn Left
        break;
      default:
        break;
    }
}

//Ultrasonic Car
#define SONAR_MODE_CRUISE_SPEED (40+oa_VoltageCompensationToSpeed)
typedef uint8_t u8;
#define COUNT_GET_SONAR 1
void Ultrasonic_Car() {
  int distance[3], tempDistance[3][5], sumDisntance;
  static u8 leftToRight = 0, servoAngle = 0, lastServoAngle = 0;  //
  const u8 scanAngle[2][3] = { { 150, 90, 30 }, { 30, 90, 150 } };
  int speedOffset = oa_VoltageCompensationToSpeed;
  for (int i = 0; i < 3; i++) {
    servoAngle = scanAngle[leftToRight][i];
    Servo_1_Angle(servoAngle);
    if (lastServoAngle != servoAngle) {
      delay(100);
    }
    lastServoAngle = servoAngle;
    for (int j = 0; j < COUNT_GET_SONAR; j++) {
      tempDistance[i][j] = Get_Sonar();
      delayMicroseconds(2 * SONIC_TIMEOUT);
      sumDisntance += tempDistance[i][j];
    }
    if (leftToRight == 0) {
      distance[i] = sumDisntance / COUNT_GET_SONAR;
    } else {
      distance[2 - i] = sumDisntance / COUNT_GET_SONAR;
    }
    sumDisntance = 0;
  }
  leftToRight = (leftToRight + 1) % 2;
  // Serial.println("Sonar : " + String(distance[0]) + " " + String(distance[1]) + " " + String(distance[2]));
  if (distance[1] < OBSTACLE_DISTANCE) {                                                               //Too little distance ahead
    if (distance[0] > distance[2] && distance[0] > OBSTACLE_DISTANCE) {                                //Left distance is greater than right distance
      Motor_Move(-(SONAR_MODE_CRUISE_SPEED + speedOffset), -(SONAR_MODE_CRUISE_SPEED + speedOffset));  //Move back
      delay(100);
      Motor_Move(-(SONAR_MODE_CRUISE_SPEED + speedOffset), (SONAR_MODE_CRUISE_SPEED + speedOffset));
    } else if (distance[0] < distance[2] && distance[2] > OBSTACLE_DISTANCE) {                         //Right distance is greater than left distance
      Motor_Move(-(SONAR_MODE_CRUISE_SPEED + speedOffset), -(SONAR_MODE_CRUISE_SPEED + speedOffset));  //Move back
      delay(100);
      Motor_Move((SONAR_MODE_CRUISE_SPEED + speedOffset), -(SONAR_MODE_CRUISE_SPEED + speedOffset));
    } else {  //Get into the dead corner, move back, then turn.
      Motor_Move(-(SONAR_MODE_CRUISE_SPEED + speedOffset), -(SONAR_MODE_CRUISE_SPEED + speedOffset));
      delay(100);
      Motor_Move(-(SONAR_MODE_CRUISE_SPEED + speedOffset), (SONAR_MODE_CRUISE_SPEED + speedOffset));
    }
  } else {                                                                                             //No obstacles ahead
    if (distance[0] < OBSTACLE_DISTANCE_LOW) {                                                         //Obstacles on the left front.
      Motor_Move(-(SONAR_MODE_CRUISE_SPEED + speedOffset), -(SONAR_MODE_CRUISE_SPEED + speedOffset));  //Move back
      delay(100);
      Motor_Move((70 + speedOffset), (20 + speedOffset));
    } else if (distance[2] < OBSTACLE_DISTANCE_LOW) {                                                  //Obstacles on the right front.
      Motor_Move(-(SONAR_MODE_CRUISE_SPEED + speedOffset), -(SONAR_MODE_CRUISE_SPEED + speedOffset));  //Move back
      delay(100);
      Motor_Move((20 + speedOffset), (70 + speedOffset));
    } else {  //Cruising
      Motor_Move((30 + speedOffset), (30 + speedOffset));
    }
  }
}

//////////////////////Car drive area////////////////////////////////////////
int carFlag = 0;
//set car mode
void Car_SetMode(int mode) {
  carFlag = mode;
}

//select it to run car
void Car_Select(int mode) {
  switch (mode) {
    case CAR_MODE_LIGHT_TRACING:
      Light_Car();
      break;
    case CAR_MODE_LINE_TRACKING:
      Track_Car();
      break;
    case CAR_MODE_SONAR:
      Ultrasonic_Car();
      break;
    case CAR_MODE_MANUAL:
    default:
      break;
  }
}

int Check_Module_value = 0;
bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}

int headModuleValue = 0;
int lastHeadModuleValue = 0;
void Emotion_and_Ultrasonic_Setup() {

  if (!i2CAddrTest(0x71)) {
    Check_Module_value = SONAR_IS_ESIST;
    headModuleValue = 1;
  } else {
    headModuleValue = 2;
    Check_Module_value = MATRIX_IS_EXIST;
  }
  if (headModuleValue != lastHeadModuleValue) {
    if (headModuleValue == 1) {  //
      Serial.print("\n Ultrasonic reInit.\n");
      Ultrasonic_Setup();
    } else if (headModuleValue == 2) {  //
      Serial.print("\n Emotion reInit.\n");
      delay(100);
      Emotion_Setup();
    }
    lastHeadModuleValue = headModuleValue;
  }
}