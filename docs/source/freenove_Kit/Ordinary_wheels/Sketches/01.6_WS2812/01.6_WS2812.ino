/**********************************************************************
  Product     : Freenove 4WD Car for Raspberry Pi Pico (W)
  Description : Basic usage of LEDPixel, 
                Make the strip light up in different colors gradually.
  Auther      : www.freenove.com
  Modification: 2023/04/10
**********************************************************************/
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Freenove_4WD_Car_WS2812.h"

void setup() {
 WS2812_Setup();      //WS2812 initialization
}

void loop() {
  WS2812_Show(5);
}
