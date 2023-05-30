/**********************************************************************
  Filename    : Camera Car
  Product     : Freenove 4WD Car for Pico W
  Auther      : www.freenove.com
  Modification: 2023/04/15
**********************************************************************/
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>
#include "Freenove_4WD_Car_WiFi.h"
#include "Freenove_4WD_Car_Emotion.h"
#include "Freenove_4WD_Car_WS2812.h"
#include "Freenove_4WD_Car_For_Pico_W.h"

#define UPLOAD_VOL_TIME 3000
long int lastUploadVoltageTime;
#define UPLOAD_LIGHTVOL_TIME 500
long int lastUploadLIGHTADCTime;
#define UPLOAD_LINEVOL_TIME 200
long int lastUploadLINEVOLTime;
long int lastUploadSONARVOLTime;
int buzzer_frequency = 0;
int CAR_MODE_VOL = 0;
int LASt_CAR_MODE_VOL = 0;

String CmdArray[8];
int paramters[8];
int sendOnceModuleCheck = 1;
int cmdFlag;

//WiFi parameter setting
char ssid_Router[]     = "********";      //Modify according to your router name
char password_Router[] = "********";      //Modify according to your router password
char ssid_AP[]         = "Sunshine";      //Pico W turns on an AP and calls it Sunshine
char password_AP[]     = "Sunshine";      //Set your AP password for Pico W to Sunshine
WiFiServer server_Cmd(4002);

void setup() {
  Buzzer_Setup();                //Buzzer initialization
  Serial.begin(115200);
  WiFi_Setup(0);                 //Set mode. When the parameter is 1, AP mode is enabled. If the parameter is 0, the STA mode is enabled.
  server_Cmd.begin(4002);        //Start the command server
  server_Cmd.setNoDelay(true);   //Set no delay in sending and receiving data
  Wire.begin();
  Motor_Setup();                 //Motor initialization
  Servo_Setup();                 //Servo initialization
  WS2812_Setup();                //WS2812 initialization
  Emotion_and_Ultrasonic_Setup();//Emotion initialization or Ultrasonic initialization
  Photosensitive_Setup();        //Light initialization
  Track_Setup();                 //Track initialization
  Servo_1_Angle(90);
  delay(500);
}

void loop() {
  WiFiClient client = server_Cmd.available();  //listen for incoming clients
  if (client) {                                //if you get a client
    Serial.println("Cmd_Server connected to a client.");
    while (client.connected()) {
      if (sendOnceModuleCheck == 1) {
        if (Check_Module_value == SONAR_IS_ESIST)
          cmdFlag = SONAR_IS_ESIST;
        else
          cmdFlag = MATRIX_IS_EXIST;
        sendOnceModuleCheck = 0;
        client.print("A#" + String(cmdFlag) + "\n");
      }                                                         //loop while the client's connected
      if (client.available()) {                                 //if there's bytes to read from the client
        String inputStringTemp = client.readStringUntil('\n');  //Read the command by WiFi
        Serial.println(inputStringTemp);                        //Print out the command received by WiFi
        Get_Command(inputStringTemp);
        if (CmdArray[0] == CMD_LED_MOD)  //Set the display mode of car colored lights
        {
          WS2812_SetMode(paramters[1]);
        }
        if (CmdArray[0] == CMD_LED)  //Set the color and brightness of the car lights
        {
          WS2812_Set_Color_1(paramters[1], paramters[2], paramters[3], paramters[4]);
        }
        if (CmdArray[0] == CMD_MATRIX_MOD)  //Set the display mode of the LED matrix
        {
          if (Check_Module_value == MATRIX_IS_EXIST) {
            Emotion_SetMode(paramters[1]);  //Display
            Serial.print(" \n matrix is exist !!! \n");
          }
          if (Check_Module_value != MATRIX_IS_EXIST) {
            // Buzzer_Variable(2000, 50, 2);
            client.print("A#" + String(SONAR_IS_ESIST) + "\n");
            Serial.print(" \n sonar is exist !!! \n");
          }
        }
        if (CmdArray[0] == CMD_BUZZER)  //Buzzer control command
        {
          tone(2, paramters[1]);
        }
        if (CmdArray[0] == CMD_POWER) {  //Power query command
          float battery_voltage = Get_Battery_Voltage();
          client.print(CMD_POWER);
          client.print(INTERVAL_CHAR);
          client.print(battery_voltage);
          client.print(ENTER);
        }
        if (CmdArray[0] == CMD_MOTOR) {  //Network control car movement command
          Car_SetMode(0);
          if (paramters[1] == 0 && paramters[2] == 0) {
            Motor_Move(0, 0);  //Stop the car
          } else               //If the parameters are not equal to 0
          {
            Motor_Move(paramters[1], paramters[2]);
          }
        }
        if (CmdArray[0] == CMD_SERVO) {  //Network control servo motor movement command
          Servo_1_Angle(paramters[1]);
        }
        if (CmdArray[0] == CMD_CAR_MODE) {  //Car command Mode
          oa_CalculateVoltageCompensation();
          if (paramters[1] == CAR_MODE_LIGHT_TRACING)  //Light seeking car command
          {
            LASt_CAR_MODE_VOL = 1;
            Car_SetMode(1);
          } else if (paramters[1] == CAR_MODE_LINE_TRACKING)  //Tracking car command
          {
            LASt_CAR_MODE_VOL = 1;
            Car_SetMode(2);
          } else if (paramters[1] == CAR_MODE_SONAR)  //Ultrasonic car command
          {
            if (Check_Module_value == SONAR_IS_ESIST) {
              LASt_CAR_MODE_VOL = 1;
              Car_SetMode(CAR_MODE_SONAR);
            }
            if (Check_Module_value != SONAR_IS_ESIST) {
              Car_SetMode(CAR_MODE_MANUAL);
              // Buzzer_Variable(2000, 50, 2);
              client.print("A#" + String(MATRIX_IS_EXIST) + "\n");
            }
          } else if (paramters[1] == 0) {
            LASt_CAR_MODE_VOL = 2;
            Car_SetMode(0);
          }
          if (CAR_MODE_VOL != LASt_CAR_MODE_VOL) {
            if (CAR_MODE_VOL == 1) {
              emotion_task_mode = 0;  //Display
              Motor_Move(0, 0);       //Stop the car
              Servo_1_Angle(90);
              delay(100);
              isLightModeFirstStarting = true;
            }
            CAR_MODE_VOL = LASt_CAR_MODE_VOL;
          }
        }
        //Clears the command array and parameter array
        memset(CmdArray, 0, sizeof(CmdArray));
        memset(paramters, 0, sizeof(paramters));
      }
      if (millis() - lastUploadVoltageTime > UPLOAD_VOL_TIME) {
        float battery_voltage = Get_Battery_Voltage();
        client.print("P#" + String(battery_voltage) + "\n");
        lastUploadVoltageTime = millis();
      }
      Emotion_and_Ultrasonic_Setup();
      if (Check_Module_value == MATRIX_IS_EXIST) {
        Emotion_Show(emotion_task_mode);  //Led matrix display function
      } else if (Check_Module_value == SONAR_IS_ESIST) {
      }
      WS2812_Show(ws2812_task_mode);  //Car color lights display function
      Car_Select(carFlag);            //Pico W Car mode selection function
      if (carFlag == CAR_MODE_LIGHT_TRACING) {
        if (millis() - lastUploadLIGHTADCTime > UPLOAD_LIGHTVOL_TIME) {
          int leftADCVoltage = getLeftPhotosensitiveADCValue();
          int rightADCVoltage = getRightPhotosensitiveADCValue();
          client.print("C#1#" + String(leftADCVoltage) + "#" + String(rightADCVoltage) + "\n");
          lastUploadLIGHTADCTime = millis();
        }
      }
      if (carFlag == CAR_MODE_LINE_TRACKING) {
        if (millis() - lastUploadLINEVOLTime > UPLOAD_LINEVOL_TIME) {
          Track_Read();
          client.print("C#2#" + String(sensorValue[0]) + String(sensorValue[1]) + String(sensorValue[2]) + "\n");
          lastUploadLINEVOLTime = millis();
        }
      }
      if (carFlag == CAR_MODE_SONAR && Check_Module_value == SONAR_IS_ESIST) {
        float distance = Get_Sonar();
        client.print("C#3#" + String(distance) + "\n");
        lastUploadSONARVOLTime = millis();
      }
    }
    client.stop();  //close the connection:
    Serial.println("Command Client Disconnected.");
    sendOnceModuleCheck = 1;
    carFlag = CAR_MODE_MANUAL;
  }
}

void Get_Command(String inputStringTemp) {
  int string_length = inputStringTemp.length();
  for (int i = 0; i < 8; i++) {  //Parse the command received by WiFi
    int index = inputStringTemp.indexOf(INTERVAL_CHAR);
    if (index < 0) {
      if (string_length > 0) {
        CmdArray[i] = inputStringTemp;           //Get command
        paramters[i] = inputStringTemp.toInt();  //Get parameters
      }
      break;
    } else {
      string_length -= index;                                  //Count the remaining words
      CmdArray[i] = inputStringTemp.substring(0, index);       //Get command
      paramters[i] = CmdArray[i].toInt();                      //Get parameters
      inputStringTemp = inputStringTemp.substring(index + 1);  //Update string
    }
  }
}
