/**********************************************************************
  Filename    : Tracking_Car.ino
  Product     : Freenove 4WD Car for Raspberry Pi Pico (W)
  Auther      : www.freenove.com
  Modification: 2023/07/10
**********************************************************************/

#include <Arduino.h>
#include "Freenove_4WD_Car_For_Pico_W.h"

#define SPEED_LV4   ( 90 )
#define SPEED_LV3   ( 75 )
#define SPEED_LV2   ( 60 )
#define SPEED_LV1   ( 45 )

void setup()
{
  Track_Setup();      //Trace module initialization
  Motor_Setup();      //Motor initialization
  Emotion_Setup();    //Emotion initialization
}

void loop()
{
  Track_Read();
  switch (sensorValue[3])
  {
    case 2:   //010
    case 5:   //101
      showArrow(1, 100);
      Motor_M_Move(SPEED_LV1 , SPEED_LV1, SPEED_LV1, SPEED_LV1);  //Move Forward
      break;
    case 0:   //000
      Motor_M_Move(SPEED_LV1 , SPEED_LV1 ,SPEED_LV1 ,SPEED_LV1);  //Move Forward
      break;
    case 7:   //111
      eyesBlink1(100);
      Motor_M_Move(0, 0, 0, 0);  //Stop
      break;
    case 4:   //100
    case 6:   //110
      wheel(2, 100);
      Motor_M_Move(-SPEED_LV4, -SPEED_LV4, SPEED_LV3, SPEED_LV3);  //Turn Left
      break;
    case 1:   //001
    case 3:   //011
      wheel(1, 100);
      Motor_M_Move(SPEED_LV3, SPEED_LV3, -SPEED_LV4, -SPEED_LV4);  //Turn Right
      break;
    default:
      break;
  }
}
