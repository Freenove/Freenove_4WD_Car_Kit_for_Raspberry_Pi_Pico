#ifndef _EMOTION_H
#define _EMOTION_H

#include "Freenove_4WD_Car_For_Pico_W.h"

extern int emotion_task_mode;
extern int emotion_count;

void Emotion_Setup(int address = 0x71);                 //Initializes the Led Matrix
void Emotion_Show(int mode);       //Display:0-Display off,1-Turn the eyes,2-blink eyes,3-smile,4-cry,5-left-wheel,6-right-wheel
void Emotion_SetMode(int mode);    //set the emotion show mode

void clearEmtions(void);                                //clear all
void eyesRotate(int delay_ms);                          //rotate eyes
void eyesBlink(int delay_ms);                           //blink eyes
void eyesSmile(int delay_ms);                           //smile
void eyesCry(int delay_ms);                             //cry
void wheel(int mode, int delay_ms);                     //wheel
void staticEmtions(int emotion);                        //show static emotion
/*
  static emotion show
  0- adoration       1- coldness         2- astonishment      3- depression        4- squinting laughter
  5- Wacky Smile     6- Clouds Smile     7- Question Mark     8- Apathy            9- Loss 1
  10- upset 2        11- shy smile       12- drag             13- unhappy          14- kind
  15- Surprised      16- Stare           17- Frustrated       18- Examine          19- Heart shape
  20 - astonished
  0-崇拜    1-冷酷     2-惊愕    3-沮丧    4-眯眼笑
  5-搞怪笑  6-云朵笑    7-问号    8-冷漠    9-失落1
  10-失落2  11-害羞笑   12-拽     13-不开心 14-慈祥
  15-惊讶   16-注视     17-受挫折 18-审视   19-心形
  20-惊呆
*/
void staticEmtions(int emotion);   //show static emotion

#endif













//
