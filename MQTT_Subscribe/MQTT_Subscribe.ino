/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "khD4jqMtp22gGSPXRPAg1yYMBEFc8Y" // Your Ubidots TOKEN
#define WIFINAME "GO-SOLO" //Your SSID
#define WIFIPASS "swatcat1234" //Your Wifi Pass
#define MQTTCLIENTNAME "HEYBABY123" // Your MQTT Client Name, it must be unique so we recommend to choose a random ASCCI name
#define MQTTCLIENTNAME "HEYBABY12"

Ubidots client(TOKEN, MQTTCLIENTNAME);
Ubidots client1(TOKEN, MQTTCLIENTNAME);
int value = 0;
/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.println((char)payload[i]);
    value = (int) payload[i];
    
  }
  Serial.println(value);
   if (value == 49)
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (value == 48)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }

  
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  client.ubidotsSubscribe("UNO","Temp+Count"); //Insert the dataSource and Variable's Labels
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      client.ubidotsSubscribe("UNO","Temp"); //Insert the dataSource and Variable's Labels
      }
  client.loop();
  }
