/**********************************************************************
  Filename    : Tcp Serrver (Only Pico W)
  Product     : Freenove 4WD Car for Raspberry Pi Pico W 
  Auther      : www.freenove.com
  Modification: 2023/04/13
**********************************************************************/
#include <WiFi.h>
#include <WiFiClient.h>

const char* ssid_Router     =   "********";   //Modify according to your router name
const char* password_Router =   "********";   //Modify according to your router password
const char* ssid_AP         =   "********";   //Raspberry Pi Pico W turns on an AP and calls it Sunshine
const char* password_AP     =   "********";   //Set your AP password for Pico W to Sunshine
WiFiServer server_Cmd(4002);

void setup() {
  Serial.begin(115200);
  Serial.println();
  WiFi.softAP(ssid_AP, password_AP);//Turn on Raspberry Pi Pico W's AP feature
  server_Cmd.begin(4002);           //Turn on Cmd server
  server_Cmd.setNoDelay(true);      //Set no delay in sending and receiving data

  WiFi.disconnect(true);
  WiFi.begin(ssid_Router, password_Router);//Make a connector request to the router
  Serial.print("Connecting ");
  Serial.print(ssid_Router);
  int timeout=0;
  while (WiFi.connected() != true) { //If the connection fails, wait half a second for another connection request
    delay(500);
    Serial.print(".");
    timeout++;
    if(timeout==20)
      break;
  }
  
  Serial.print("\nCamera Ready! Use '");
  // Serial.print(WiFi.softAPIP());
  // Serial.print(" or ");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect in Freenove app.");
}

void loop() {
  WiFiClient client = server_Cmd.available();//listen for incoming clients
  if (client)                                //if you get a client,
  {
    Serial.println("Command Server connected to a client.");
    while (client.connected()) {//loop while the client's connected
      if (client.available()) { //if there's bytes to read from the client,
        String dataBuffer = client.readStringUntil('\n') + String("\n"); //read data
        Serial.print(dataBuffer);//print it out the serial monitor
      }
    }
    client.stop();// close the connection:
    Serial.println("Command Client Disconnected.");
  }
}
