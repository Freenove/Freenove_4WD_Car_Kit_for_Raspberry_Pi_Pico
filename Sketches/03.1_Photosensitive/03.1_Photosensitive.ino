/**********************************************************************
  Filename    : Photosensitive_Sensor.ino
  Product     : Freenove 4WD Car for Raspberry Pi Pico (W)
  Auther      : www.freenove.com
  Modification: 2023/04/13
**********************************************************************/
#define Left_PHOTOSENSITIVE_PIN 27  //Define the pins that Raspberry Pi Pico reads photosensitive
#define Right_PHOTOSENSITIVE_PIN 28 //Define the pins that Raspberry Pi Pico reads photosensitive
int getLeftPhotosensitiveADCValue;  //Define a variable to store the left photosensitive adc value
int getRightPhotosensitiveADCValue; //Define a variable to store the right photosensitive adc value

void setup()
{
  pinMode(Left_PHOTOSENSITIVE_PIN, INPUT);//Configure the pins for input mode
  pinMode(Right_PHOTOSENSITIVE_PIN, INPUT);//Configure the pins for input mode
  Serial.begin(115200);          //Initialize the serial port and set the baud rate to 115200
}

void loop()
{
  getLeftPhotosensitiveADCValue = analogRead(Left_PHOTOSENSITIVE_PIN);//Read ADC1 value value
  getRightPhotosensitiveADCValue = analogRead(Right_PHOTOSENSITIVE_PIN);//Read ADC2 value value
  Serial.print("The photosensitive ADC on the left: ");
  Serial.println(getLeftPhotosensitiveADCValue);       //Print the photosensitive ADC value on the left
  Serial.print("The photosensitive ADC on the right: ");
  Serial.println(getRightPhotosensitiveADCValue);      //Print the photosensitive ADC value on the right
  delay(500);
}

