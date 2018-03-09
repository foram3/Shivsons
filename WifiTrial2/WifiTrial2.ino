/*
 *  HTTP over TLS (HTTPS) example sketch
 *
 *  This example demonstrates how to use
 *  WiFiClientSecure class to access HTTPS API.
 *  We fetch and display the status of
 *  esp8266/Arduino project continuous integration
 *  build.
 *
 *  Created by Ivan Grokhotkov, 2015.
 *  This example is in public domain.
 */

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UbidotsMicroESP8266.h>
//#include <UbidotsArduino.h>


#define ssid  "Ronak"
#define password  "ronak62a"

// Ubidots Data

#define tempVarId  "586996d57625425717591bc1"
String humVarId = "5869434d762542570e5fe3b0";
#define token  "khD4jqMtp22gGSPXRPAg1yYMBEFc8Y"


const char* host = "things.ubidots.com";
const int httpsPort = 80;

Ubidots client(token);

// Use web browser to view and copy
// SHA1 fingerprint of the certificate


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  
  client.wifiConnection(ssid, password);
  client.ubidotsSubscribe("esp8266","temperature");
 
   
}
  

void loop() {

   if(!client.connected()){
      client.reconnect();
      client.ubidotsSubscribe("UNO","Temp"); //Insert the dataSource and Variable's Labels
      }
  client.loop();

  
  
  if (value == 1)
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (value == 0)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }

  delay(500);  
  
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}



