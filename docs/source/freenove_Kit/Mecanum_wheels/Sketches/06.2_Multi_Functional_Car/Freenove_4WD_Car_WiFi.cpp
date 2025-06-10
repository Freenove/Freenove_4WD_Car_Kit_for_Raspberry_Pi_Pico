#include "Freenove_4WD_Car_WiFi.h"
#include "Freenove_4WD_Car_For_Pico_W.h"

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>


///////////////////WiFi drive area////////////////////////////////////////
bool WiFi_MODE = 1;
int times = 6;

IPAddress local_IP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

//Initialize WiFi function
void WiFi_Setup(bool WiFi_Mode) {
  if (WiFi_Mode == 0) {
    WiFi_MODE = 0;
    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(ssid_Router, password_Router);
    Serial.print("\nWaiting for WiFi... ");
    while (WiFi.connected() != true) {
      Serial.print(".");
      delay(500);
    }
    IPAddress local_ip = WiFi.localIP();
    Serial.println("");
    Serial.println("\nWiFi connected");
    Serial.print("Use your phone to connect to WiFi: ");
    Serial.println(ssid_Router);
    Serial.print("\nThe password for WiFi is: ");
    Serial.println(password_Router);
    Serial.print("\nThen you can enter: '");
    Serial.print(local_ip);
    Serial.println("' to connect the car in Freenove app.");
    
    Buzzer_Alarm(1);
    delay(100);
    Buzzer_Alarm(0);
  } else {
    WiFi_MODE = 1;
    WiFi.disconnect(true);
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(ssid_AP, password_AP);
    while (times--) {
      Serial.print(".");
      delay(500);
    }
    Serial.print("\nUse your phone to connect to WiFi: ");
    Serial.println(ssid_AP);
    Serial.print("\nThe password for WiFi is: ");
    Serial.println(password_AP);
    Serial.print("\nThen you can enter: '");
    Serial.print(local_IP);
    Serial.println("' to connect the car in Freenove app.");

    Buzzer_Alarm(1);
    delay(100);
    Buzzer_Alarm(0);
  }
}
