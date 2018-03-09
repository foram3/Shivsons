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
#include "UbidotsESPMQTT.h"
#include <ESP8266WiFi.h> 



#define ssid  "GO-SOLO"
#define password  "swatcat1234"
#define MQTTCLIENTNAME "forampatel11"

// Ubidots Data

#define tempVarId  "586996d57625425717591bc1"
String humVarId = "5869434d762542570e5fe3b0";
#define token  "khD4jqMtp22gGSPXRPAg1yYMBEFc8Y"


const char* VarName  = "/v1.6/devices/UNO/Temp";
float value;
char mqtt_server[] = "things.ubidots.com"; // the ubidots.com MQTT server
int mqtt_port = 1883;




WiFiClient espClient;            // create an instance of the wifi client
PubSubClient client(espClient);

// Use web browser to view and copy
// SHA1 fingerprint of the certificate


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  connectWifi();
  client.setServer(mqtt_server, mqtt_port);
  reconnect();
  
 
 
   
}
  

void loop() {

  if (WiFi.status() != WL_CONNECTED)
    connectWifi();
    
  if(!client.connected()){
    Serial.println("Not Connected, Trying to reconnect!");
      if (client.connect("mqtt://things.ubidots.com", token, ""))
        {
           Serial.println("connected");
        }
   }
  client.loop();

  if(client.connected())
  {
  client.publish(VarName,"300");
  Serial.println(value);
  }
//  
//  if (value == 1)
//  {
//    digitalWrite(LED_BUILTIN, LOW);
//  }
//  else if (value == 0)
//  {
//    digitalWrite(LED_BUILTIN, HIGH);
//  }

  delay(50);  
  
}


void connectWifi()
{
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);

  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected to wifi");
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // Boolean connect(const char* clientId, const char* username, const char* password);
    if (client.connect("mqtt://things.ubidots.com", "khD4jqMtp22gGSPXRPAg1yYMBEFc8Y", ""))
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // client.publish("/users/peejster/temp/ambient", "0");
      // ... and resubscribe
      //client.subscribe("inTopic");
    }
      else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

