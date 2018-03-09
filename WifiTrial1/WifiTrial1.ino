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


const char* ssid = "Ronak";
const char* password = "ronak62a";

// Ubidots Data

String tempVarId = "586996d57625425717591bc1";
String humVarId = "5869434d762542570e5fe3b0";
String token = "khD4jqMtp22gGSPXRPAg1yYMBEFc8Y";


const char* host = "things.ubidots.com";
const int httpsPort = 80;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  
  String varString = "[{\"variable\": " + tempVarId + "\", \"value\":" + String(100) + "}";
  varString += ",{\"variable\": \"" + humVarId + "\", \"value\":" + String(1000) + "}]";
  int   num = varString.length();

  int cont = 0;
  while(cont == 0)
  {
  Serial.println("Trying connection!");
  if (client.connect(host, httpsPort)) {
    Serial.println("connection success!");
    cont = 1;
  }
  delay(3000);
  }
    client.println("POST /api/v1.6/collections/values HTTP/1.1");
    Serial.println("POST /api/v1.6/collections/values HTTP/1.1");
    client.println("Content-Type: application/json");
    Serial.println("Content-Type: application/json");
    client.println("Content-Length: "+String(num));
    Serial.println("Content-Length: "+String(num));
    client.println("X-Auth-Token: "+token);
    Serial.println("X-Auth-Token: "+token);
    client.println("Host: things.ubidots.comn");
    Serial.println("Host: things.ubidots.comn");
    client.print(varString);
    Serial.print(varString+"n");

  Serial.println("request sent");


 boolean sta = client.connected();
  Serial.println("Connection ["+String(sta)+"]");
  if (!client.connected())   {
   Serial.println();
   Serial.println("disconnecting.");
   client.stop();
  }
 
  Serial.println("Reading..");
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  client.flush();
  client.stop();
}
  

void loop() {
  // put your main code here, to run repeatedly:

}
