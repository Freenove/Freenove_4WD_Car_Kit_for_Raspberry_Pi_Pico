#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Freenove_4WD_Car_WS2812.h"

int ws2812_task_mode = 0;
int ws2812_strip_time_now;
int ws2812_strip_time_next;
unsigned char ws2812_strip_color_1[12][3];
unsigned char ws2812_strip_color_2[12][3];

byte m_color[5][3] = { { 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 255 }, { 255, 255, 255 }, { 0, 0, 0 } };

Adafruit_NeoPixel ws2812_strip(LEDS_COUNT, WS2812_PIN, NEO_GRB + NEO_KHZ800);

//Set the display color1 for WS2812
void WS2812_Set_Color_1(int number, unsigned char color_1, unsigned char color_2, unsigned char color_3)  //Set the display color1 for WS2812
{
  for (int i = 0; i < 12; i++) {
    if ((number >> i) & 0x01 == 0x01) {
      ws2812_strip_color_1[i][0] = constrain(color_1, 0, 255);
      ws2812_strip_color_1[i][1] = constrain(color_2, 0, 255);
      ws2812_strip_color_1[i][2] = constrain(color_3, 0, 255);
    }
  }
}

//Set the display color2 for WS2812
void WS2812_Set_Color_2(int number, unsigned char color_1, unsigned char color_2, unsigned char color_3)  //Set the display color1 for WS2812
{
  if (number == 0) {
    for (int i = 0; i < 12; i++) {
      ws2812_strip_color_2[i][0] = constrain(color_1, 0, 255);
      ws2812_strip_color_2[i][1] = constrain(color_2, 0, 255);
      ws2812_strip_color_2[i][2] = constrain(color_3, 0, 255);
    }
  } else if (number > 0 && number <= 12) {
    ws2812_strip_color_2[number - 1][0] = constrain(color_1, 0, 255);
    ws2812_strip_color_2[number - 1][1] = constrain(color_2, 0, 255);
    ws2812_strip_color_2[number - 1][2] = constrain(color_3, 0, 255);
  }
}

//Close the display WS2812
void ws2812_close(void) {
  for (int i = 0; i < 12; i++)
    ws2812_strip.setPixelColor(i, 0, 0, 0);
  ws2812_strip.show();
}

int ws2812_following_number = 0;
int following_brightness = 100;


//WS2812 Flow display
void ws2812_following(void)
{
  ws2812_strip_time_next = millis();
  if (ws2812_strip_time_next - ws2812_strip_time_now > 100)
  {
    ws2812_strip_time_now = ws2812_strip_time_next;
    for (int i = 0; i < ws2812_following_number; i++)
      ws2812_strip.setPixelColor(i, ws2812_strip_color_1[i][0], ws2812_strip_color_1[i][1], ws2812_strip_color_1[i][2]);
    for (int i = ws2812_following_number; i < 8; i++)
      ws2812_strip.setPixelColor(i, 0, 0, 0);
    ws2812_strip.show();
    ws2812_following_number++;
    if (ws2812_following_number == 9)
      ws2812_following_number = 0;
  }
}

//WS2812 static display
void ws2812_rgb(void) {
  ws2812_strip_time_next = millis();
  if (ws2812_strip_time_next - ws2812_strip_time_now > 100) {
    ws2812_strip_time_now = ws2812_strip_time_next;
    for (int i = 0; i < 12; i++)
      ws2812_strip.setPixelColor(i, ws2812_strip_color_1[i][0], ws2812_strip_color_1[i][1], ws2812_strip_color_1[i][2]);
    ws2812_strip.show();
  }
}

int ws2812_blink_flag = 0;
//WS2812 blink display
void ws2812_blink(void) {
  ws2812_strip_time_next = millis();
  if (ws2812_strip_time_next - ws2812_strip_time_now > 500 && ws2812_blink_flag == 0) {
    ws2812_blink_flag = 1;
    ws2812_strip_time_now = ws2812_strip_time_next;
    for (int i = 0; i < 12; i++)
      ws2812_strip.setPixelColor(i, ws2812_strip_color_1[i][0], ws2812_strip_color_1[i][1], ws2812_strip_color_1[i][2]);
    ws2812_strip.show();
  } else if (ws2812_strip_time_next - ws2812_strip_time_now > 500 && ws2812_blink_flag == 1) {
    ws2812_blink_flag = 0;
    ws2812_strip_time_now = ws2812_strip_time_next;
    for (int i = 0; i < 12; i++)
      ws2812_strip.setPixelColor(i, ws2812_strip_color_2[i][0], ws2812_strip_color_2[i][1], ws2812_strip_color_2[i][2]);
    ws2812_strip.show();
  }
}

int ws2812_breathe_flag = 0;
int breathe_brightness = 0;
//WS2812 breathe display
void ws2812_breathe(void) {
  ws2812_strip_time_next = millis();
  if ((ws2812_strip_time_next - ws2812_strip_time_now > 5) && (ws2812_breathe_flag == 0)) {
    ws2812_strip_time_now = ws2812_strip_time_next;
    breathe_brightness++;
    for (int i = 0; i < 12; i++)
      ws2812_strip.setPixelColor(i, ws2812_strip_color_1[i][0] * breathe_brightness / 255, ws2812_strip_color_1[i][1] * breathe_brightness / 255, ws2812_strip_color_1[i][2] * breathe_brightness / 255);
    ws2812_strip.show();
    if (breathe_brightness >= 255)
      ws2812_breathe_flag = 1;
  }
  if ((ws2812_strip_time_next - ws2812_strip_time_now > 5) && (ws2812_breathe_flag == 1)) {
    ws2812_strip_time_now = ws2812_strip_time_next;
    breathe_brightness--;
    for (int i = 0; i < 12; i++)
      ws2812_strip.setPixelColor(i, ws2812_strip_color_1[i][0] * breathe_brightness / 255, ws2812_strip_color_1[i][1] * breathe_brightness / 255, ws2812_strip_color_1[i][2] * breathe_brightness / 255);
    ws2812_strip.show();
    if (breathe_brightness <= 0)
      ws2812_breathe_flag = 0;
  }
}

int rainbow_count = 0;
//WS2812 rainbow display
void ws2812_rainbow(void) {
  ws2812_strip.setBrightness(255);
  ws2812_strip_time_next = millis();
  if (ws2812_strip_time_next - ws2812_strip_time_now > 5) {
    ws2812_strip_time_now = ws2812_strip_time_next;
    rainbow_count++;
    for (int i = 0; i < LEDS_COUNT; i++)
      ws2812_strip.setPixelColor(LEDS_COUNT - 1 - i, Wheel((i * 256 / LEDS_COUNT + rainbow_count) & 255));
    ws2812_strip.show();
    if (rainbow_count > 255)
      rainbow_count = 0;
  }
}

int Wheel(byte pos) {
  int WheelPos = pos % 0xff;
  if (WheelPos < 85) {
    return ((255 - WheelPos * 3) << 16) | ((WheelPos * 3) << 8);
    Serial.println("ws28121" + String(WheelPos));
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return (((255 - WheelPos * 3) << 8) | (WheelPos * 3));
    Serial.println("ws28122" + String(WheelPos));
  }
  WheelPos -= 170;
  return ((WheelPos * 3) << 16 | (255 - WheelPos * 3));
  Serial.println("ws28123" + String(WheelPos));
}

//WS2812 initialization function
void WS2812_Setup(void) {
  ws2812_strip.begin();
  ws2812_strip.setBrightness(255);
  ws2812_close();
  WS2812_Set_Color_1(255, 0, 0, 100);
  WS2812_Set_Color_2(255, 0, 0, 0);
  ws2812_strip_time_now = millis();
}

//WS2812 set mode
void WS2812_SetMode(int mode) {
  ws2812_task_mode = constrain(mode, 0, 5);
}

//WS2812 non-blocking display function
void WS2812_Show(int mode) {
  switch (mode) {
    case 0:  //Close the WS2812
      ws2812_close();
      break;
    case 1:
      ws2812_rgb();
      break;
    case 2:
      ws2812_following();
      break;
    case 3:
      ws2812_blink();
      break;
    case 4:
      ws2812_breathe();
      break;
    case 5:
      ws2812_rainbow();
      break;
    default:
      break;
  }
}

void WS2812_Show1(int ws2812_task_mode1) {
  for (int i = 0; i < 12; i++)
    ws2812_strip.setPixelColor(i, m_color[ws2812_task_mode1][0], m_color[ws2812_task_mode1][1], m_color[ws2812_task_mode1][2]);
  ws2812_strip.show();
}