#ifndef _FREENOVE_4WD_CAR_WIFI_H
#define _FREENOVE_4WD_CAR_WIFI_H

///////////////////WiFi command area////////////////////////////////////////

#define ENTER               '\n'                  //ENTER
#define INTERVAL_CHAR       '#'                   //INTERVAL CHAR
#define CMD_MOTOR           "M"           //Motor control command
#define CMD_POWER           "P"           //Power control command
#define CMD_BUZZER          "B"           //BUZZER control command
#define CMD_SERVO           "S"           //SERVO control command
#define CMD_LED_MOD         "D"           //WS2812 control command
#define CMD_LED             "L"           //WS2812 color command
#define CMD_MATRIX_MOD      "T"           //LED MATRIX control command
#define CMD_CAR_MODE        "C"           //Car control command
#define CMD_SIGN            "A"           //Car control command
#define CMD_M_MOTOR         "N"           //Motor control command
#define CMD_CAR_ROTATE      "O"           //Car rotate command

extern char ssid_Router[]             ;    //Modify according to your router name
extern char password_Router[]         ;    //Modify according to your router password
extern char ssid_AP[]                 ;    //Pico W turns on an AP and calls it Sunshine
extern char password_AP[]             ;    //Set your AP password for Pico W to Sunshine
void WiFi_Setup(bool WiFi_Mode)       ;    //Initialize WiFi function


#endif
