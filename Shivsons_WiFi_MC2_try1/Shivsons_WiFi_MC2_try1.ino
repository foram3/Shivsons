#include "UbidotsMicroESP8266.h"
#include <SoftwareSerial.h>

#define ssid  "shivsons"
#define password  "*vijay214"
#define tempVarId  "5899d29e7625425620c729cf"
#define token  "khD4jqMtp22gGSPXRPAg1yYMBEFc8Y"

Ubidots client(token);
volatile int T120count = 0;
void setup() {
  Serial.begin(115200);
  client.wifiConnection(ssid, password);
}

void loop() {
       client.add(tempVarId,T120count);
       client.sendAll(false);
       delay(3000);
       T120count++;
}

