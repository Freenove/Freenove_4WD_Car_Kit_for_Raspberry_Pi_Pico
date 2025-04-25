/**********************************************************************
  Filename    : Tcp Serrver (Only Pico W)
  Product     : Freenove 4WD Car for Raspberry Pi Pico W 
  Auther      : www.freenove.com
  Modification: 2023/04/13
**********************************************************************/
#include <WiFi.h>

#define port 4002
const char *ssid_Router      = "********";  //input your wifi name
const char *password_Router  = "********";  //input your wifi passwords
WiFiServer  server(port);

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.printf("\nConnecting to ");
    Serial.println(ssid_Router);
    WiFi.disconnect();
    WiFi.begin(ssid_Router, password_Router);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());         
    Serial.printf("IP port: %d\n",port);            
    server.begin(port);                             
}

void loop(){
 WiFiClient client = server.accept();            // listen for incoming clients
  if (client) {                                     // if you get a client,
    Serial.println("Client connected.");
    while (client.connected()) {                    // loop while the client's connected
      if (client.available()) {                     // if there's bytes to read from the client,
        Serial.println(client.readStringUntil('\n')); // print it out the serial monitor
        while(client.read()>0);                     // clear the wifi receive area cache
      }
      if(Serial.available()){                       // if there's bytes to read from the serial monitor,
        client.print(Serial.readStringUntil('\n')); // print it out the client.
        while(Serial.read()>0);                     // clear the wifi receive area cache
      }
    }
    client.stop();                                  // stop the client connecting.
    Serial.println("Client Disconnected.");
  }
}
