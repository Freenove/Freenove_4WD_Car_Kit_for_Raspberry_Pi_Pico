#ifndef _FREENOVE_4WD_CAR_WIFI_H
#define _FREENOVE_4WD_CAR_WIFI_H

///////////////////WiFi command area////////////////////////////////////////
// #define ENTER               '\n'                  //ENTER
// #define INTERVAL_CHAR       '#'                   //INTERVAL CHAR
// #define CMD_MOTOR           "M"           //Motor control command
// #define CMD_POWER           "P"           //Power control command
// #define CMD_BUZZER          "B"           //BUZZER control command
// #define CMD_SERVO           "S"           //SERVO control command
// #define CMD_CAMERA          "C"           //SERVO control command

// #define CMD_LED_MOD         "L"           //WS2812 control command
// #define CMD_LED             "O"           //WS2812 color command
// #define CMD_MATRIX_MOD      "Q"           //LED MATRIX control command
// #define CMD_VIDEO           "V"           //VIDEO control command
// #define CMD_LIGHT           "I"           //LIGHT Car control command
// #define CMD_TRACK           "T"           //TRACK Car control command
// #define CMD_Ultrasonic         "U"      //Ultrasonic Car control command
// #define CMD_CAR_MODE        "A"           //Car control command

// #define ENTER               '\n'                  //ENTER
// #define INTERVAL_CHAR       '#'                   //INTERVAL CHAR
// #define CMD_MOTOR           "CMD_MOTOR"           //Motor control command
// #define CMD_POWER           "CMD_POWER"           //Power control command
// #define CMD_BUZZER          "CMD_BUZZER"          //BUZZER control command
// #define CMD_SERVO           "CMD_SERVO"           //SERVO control command
// // #define CMD_CAMERA          "CMD_CAMERA"          //SERVO control command

// #define CMD_LED_MOD         "CMD_LED_MOD"         //WS2812 control command
// #define CMD_LED             "CMD_LED"             //WS2812 color command
// #define CMD_MATRIX_MOD      "CMD_MATRIX_MOD"      //LED MATRIX control command
// // #define CMD_VIDEO           "CMD_VIDEO"           //VIDEO control command
// // #define CMD_LIGHT           "CMD_LIGHT"           //LIGHT Car control command
// // #define CMD_TRACK           "CMD_TRACK"           //TRACK Car control command
// // #define CMD_Ultrasonic      "CMD_Ultrasonic"      //Ultrasonic Car control command
// #define CMD_CAR_MODE        "CMD_CAR_MODE"        //Car control command


#define ENTER               '\n'                  //ENTER
#define INTERVAL_CHAR       '#'                   //INTERVAL CHAR
#define CMD_MOTOR           "M"           //Motor control command
#define CMD_POWER           "P"           //Power control command
#define CMD_BUZZER          "B"           //BUZZER control command
#define CMD_SERVO           "S"           //SERVO control command
#define CMD_LED_MOD         "D"          //WS2812 control command
#define CMD_LED             "L"           //WS2812 color command
#define CMD_MATRIX_MOD      "T"          //LED MATRIX control command
#define CMD_CAR_MODE        "C"          //Car control command
#define CMD_SIGN            "A"           //Car control command


// #define ENTER               '\n'                  //ENTER
// #define INTERVAL_CHAR       '#'                   //INTERVAL CHAR
// #define CMD_MOTOR           'M'           //Motor control command
// #define CMD_POWER           'P'           //Power control command
// #define CMD_BUZZER          'B'           //BUZZER control command
// #define CMD_SERVO           'S'           //SERVO control command
// #define CMD_LED_MOD         'D'          //WS2812 control command
// #define CMD_LED             'L'           //WS2812 color command
// #define CMD_MATRIX_MOD      'T'          //LED MATRIX control command
// #define CMD_CAR_MODE        'C'          //Car control command
// #define CMD_SIGN            'A'           //Car control command


extern char ssid_Router[]             ;    //Modify according to your router name
extern char password_Router[]         ;    //Modify according to your router password
extern char ssid_AP[]                 ;    //ESP32 turns on an AP and calls it Sunshine
extern char password_AP[]             ;    //Set your AP password for ESP32 to Sunshine
void WiFi_Setup(bool WiFi_Mode)       ;    //Initialize WiFi function


#endif
