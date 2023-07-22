#include <Arduino.h>
#include "Freenove_4WD_Car_For_Pico_W.h"
#include "Freenove_VK16K33_Lib.h"
#include "Array.h"
#include <Wire.h>

/////////////////////Servo drive area///////////////////////////////////
uint32_t Servo_Pins[] = { PIN_SERVO1 };
#define NUM_OF_ServoPINS (sizeof(Servo_Pins) / sizeof(uint32_t))
float dutyCycle1[NUM_OF_ServoPINS] = { 0.0f };
float freq1[] = { 50.0f };
RP2040_PWM* Servo_Instance[NUM_OF_ServoPINS];

int servo_1_offset = 0;  //Define the offset variable for servo 1

//servo initialization
void Servo_Setup(void) {
  for (uint8_t index = 0; index < NUM_OF_ServoPINS; index++) {
    Servo_Instance[index] = new RP2040_PWM(Servo_Pins[index], freq1[index], dutyCycle1[index]);
    if (Servo_Instance[index]) {
      Servo_Instance[index]->setPWM();
      uint32_t div = Servo_Instance[index]->get_DIV();
      uint32_t top = Servo_Instance[index]->get_TOP();
      PWM_LOGDEBUG5("TOP =", top, ", DIV =", div, ", CPU_freq =", Servo_Instance[index]->get_freq_CPU());
    }
  }
}

//Set the rotation parameters of servo 1, and the parameters are 30-150 degrees
void Servo_1_Angle(float angle) {
  angle = constrain(angle, 30, 150);
  angle = map(angle, 0.0f, 180.0f, 2500.0f, 12500.0f);
  Servo_Instance[0]->setPWM(PIN_SERVO1, 50.0f, angle / 1000.0f);
}

//Set servo 1 offset
void Set_Servo_1_Offset(int offset) {
  servo_1_offset = offset;
}

//Servo sweep function
void Servo_Sweep(int servo_id, int angle_start, int angle_end) {
  if (servo_id == 1) {
    angle_start = constrain(angle_start, 0, 180);
    angle_end = constrain(angle_end, 0, 180);
  }
  if (angle_start > angle_end) {
    for (int i = angle_start; i >= angle_end; i--) {
      if (servo_id == 1)
        Servo_1_Angle(i);
      delay(10);
    }
  }
  if (angle_start < angle_end) {
    for (int i = angle_start; i <= angle_end; i++) {
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
void Motor_M_Move(int M1_speed, int M2_speed, int M3_speed,int M4_speed) {
  int lf, lb, rf, rb;
  lf = M1_speed;
  lb = M2_speed;
  rf = M3_speed;
  rb = M4_speed;
#ifdef REVERSE_MOTOR1
  lf = -M1_speed;
#endif
#ifdef REVERSE_MOTOR2
  lb = -M2_speed;
#endif
#ifdef REVERSE_MOTOR3
  rf = -M3_speed;
#endif
#ifdef REVERSE_MOTOR4
  rb = -M4_speed;
#endif
  Motor_Move_Init(lf, lb, rf, rb);
}

//////////////////////Buzzer drive area///////////////////////////////////
void Buzzer_Setup(void) {
  pinMode(PIN_BUZZER, OUTPUT);
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
  batteryVoltage = (batteryADC / 1023.0 * 3.67) * batteryCoefficient;
  return batteryVoltage;
}

void Set_Battery_Coefficient(float coefficient) {
  batteryCoefficient = coefficient;
}

/////////////////////Photosensitive drive area//////////////////////////
//Photosensitive initialization
void Photosensitive_Setup(void) {
  pinMode(PHOTOSENSITIVE_PIN, INPUT);
}

//Gets the photosensitive resistance value
int Get_Photosensitive(void) {
  int photosensitiveADC = analogRead(PHOTOSENSITIVE_PIN);
  return photosensitiveADC;
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
  return distance;  // return the distance value
}

/////////////////////Track drive area//////////////////////////////
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

//////////////////Emotion drive area////////////////////////////////

Freenove_VK16K33 matrix = Freenove_VK16K33();
int time_before = 0;  //Record each non-blocking time
int time_count = 0;   //Record the number of non-blocking times
int time_flag = 0;    //Record the blink time

//Initialize
void Emotion_Setup() {
  matrix.init(EMOTION_ADDRESS);
  time_before = millis();
}

//Turn the eyes-1
void eyesRotate(int delay_ms) {
  int count = sizeof(eyeRotate1) / sizeof(eyeRotate1[0]);
  if (millis() - time_before >= delay_ms) {
    matrix.showStaticArray(eyeRotate1[time_count], eyeRotate2[time_count]);
    time_before = millis();
    time_count++;
    if (time_count >= count)
      time_count = 0;
  }
}

//Wink the eyes-2
void eyesBlink(int delay_ms) {
  int count = sizeof(eyeBlink) / sizeof(eyeBlink[0]);
  if (millis() - time_before >= delay_ms) {
    time_before = millis();
    time_count++;
    if (time_count >= 25) {
      time_count = 0;
      time_flag = 1;
    }
    if (time_flag == 0)
      matrix.showStaticArray(eyeBlink[0], eyeBlink[0]);
    else if (time_flag == 1) {
      matrix.showStaticArray(eyeBlink[time_count], eyeBlink[time_count]);
      if (time_count >= (count - 1)) {
        time_flag = 0;
        time_count = 0;
      }
    }
  }
}

//Smile-3
void eyesSmile(int delay_ms) {
  int count = sizeof(eyeSmile) / sizeof(eyeSmile[0]);
  if (millis() - time_before >= delay_ms) {
    matrix.showStaticArray(eyeSmile[time_count], eyeSmile[time_count]);
    time_before = millis();
    time_count++;
    if (time_count >= count)
      time_count = 0;
  }
}

//Cry-4
void eyesCry(int delay_ms) {
  int count = sizeof(eyeCry1) / sizeof(eyeCry1[0]);
  if (millis() - time_before >= delay_ms) {
    matrix.showStaticArray(eyeCry1[time_count], eyeCry2[time_count]);
    time_before = millis();
    time_count++;
    if (time_count >= count)
      time_count = 0;
  }
}

//Wink the eyes-5
void eyesBlink1(int delay_ms) {
  int count = sizeof(eyeBlink1) / sizeof(eyeBlink1[0]);
  if (millis() - time_before >= delay_ms) {
    time_before = millis();
    time_count++;
    if (time_count >= 15) {
      time_count = 0;
      time_flag = 1;
    }
    if (time_flag == 0)
      matrix.showStaticArray(eyeBlink1[0], eyeBlink1[0]);
    else if (time_flag == 1) {
      matrix.showStaticArray(eyeBlink1[time_count], eyeBlink1[time_count]);
      if (time_count >= (count - 1)) {
        time_flag = 0;
        time_count = 0;
      }
    }
  }
}

//show_arrow-6
void showArrow(int arrow_direction, int delay_ms) {
  if (arrow_direction == 1) {
    if (millis() - time_before >= delay_ms) {
      matrix.showLedMatrix(arrow_up, 4, time_count - 8);
      time_before = millis();
      time_count++;
      if (time_count > 16)
        time_count = 0;
    }
  } else if (arrow_direction == 2) {
    if (millis() - time_before >= delay_ms) {
      matrix.showLedMatrix(arrow_dowm, 4, 8 - time_count);
      time_before = millis();
      time_count++;
      if (time_count > 16)
        time_count = 0;
    }
  } else if (arrow_direction == 3) {
    if (millis() - time_before >= delay_ms) {
      matrix.showLedMatrix(arrow_left, 8 - time_count, 0);
      time_before = millis();
      time_count++;
      if (time_count > 8)
        time_count = 0;
    }
  } else if (arrow_direction == 4) {
    if (millis() - time_before >= delay_ms) {
      matrix.showLedMatrix(arrow_right, time_count, 0);
      time_before = millis();
      time_count++;
      if (time_count > 8)
        time_count = 0;
    }
  } else
    matrix.clear();
}

//wheel-7
void wheel(int mode, int delay_ms) {
  if (mode == 1) {
    int count = sizeof(wheel_left) / sizeof(wheel_left[0]);
    if (millis() - time_before >= delay_ms) {
      matrix.showStaticArray(wheel_left[time_count], wheel_left[time_count]);
      time_before = millis();
      time_count++;
      if (time_count >= count)
        time_count = 0;
    }
  } else if (mode == 2) {
    int count = sizeof(wheel_right) / sizeof(wheel_right[0]);
    if (millis() - time_before >= delay_ms) {
      matrix.showStaticArray(wheel_right[time_count], wheel_right[time_count]);
      time_before = millis();
      time_count++;
      if (time_count >= count)
        time_count = 0;
    }
  } else
    matrix.clear();
}

//Car-8
void carMove(int mode, int delay_ms) {
  if (mode == 1) {
    if (millis() - time_before >= delay_ms) {
      matrix.showLedMatrix(car_left, 8 - time_count, 0);
      time_before = millis();
      time_count++;
      if (time_count >= 8)
        time_count = 0;
    }
  } else if (mode == 2) {
    if (millis() - time_before >= delay_ms) {
      matrix.showLedMatrix(car_right, time_count, 0);
      time_before = millis();
      time_count++;
      if (time_count >= 8)
        time_count = 0;
    }
  } else
    matrix.clear();
}

//expressing love-9
void expressingLove(int delay_ms) {
  int count = sizeof(I_love_you) / sizeof(I_love_you[0]);
  if (millis() - time_before >= delay_ms) {
    matrix.showStaticArray(I_love_you[0], I_love_you[1]);
    time_before = millis();
    time_count++;
    if (time_count >= count)
      time_count = 0;
  }
}

//save water-10
void saveWater(int delay_ms) {
  int count = sizeof(save_water_left) / sizeof(save_water_left[0]);
  if (millis() - time_before >= delay_ms) {
    matrix.showStaticArray(save_water_left[time_count], save_water_right[time_count]);
    time_before = millis();
    time_count++;
    if (time_count >= count)
      time_count = 0;
  }
}
