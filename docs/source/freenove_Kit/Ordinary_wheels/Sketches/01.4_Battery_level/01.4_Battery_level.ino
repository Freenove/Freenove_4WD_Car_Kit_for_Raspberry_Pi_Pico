/**********************************************************************
  Product     : Freenove 4WD Car for Raspberry Pi Pico (W)
  Description : Read battery voltage.
  Auther      : www.freenove.com
  Modification: 2023/04/06
**********************************************************************/
#include "Freenove_4WD_Car_For_Pico_W.h"

void setup() {
  Serial.begin(115200);                     //Set the Serial Baud rate
  Servo_Setup();    //Servo initialization
}

void loop() {
  Serial.print("Battery ADC : ");
  Serial.println(Get_Battery_Voltage_ADC());//Gets the battery ADC value
  Serial.print("Battery Voltage : ");
  Serial.print(Get_Battery_Voltage());      //Get the battery voltage value
  Serial.println("V");
  delay(300);
}
