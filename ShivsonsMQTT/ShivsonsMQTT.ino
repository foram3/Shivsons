

/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"
#include <dummy.h>
#include <Ticker.h>



/****************************************
 * Define Constants
 ****************************************/
#define ssid  "shivsons"
#define password  "*vijay214"
#define MQTTCLIENTNAME "forampatel11"
#define tempVarId  "586996d57625425717591bc1"
#define token  "khD4jqMtp22gGSPXRPAg1yYMBEFc8Y"


char* VarName  = "/v1.6/devices/UNO/Temp";
const byte interruptPin = 4;
const byte indicationPin = 14;
volatile byte state = HIGH;
volatile byte uploaded = HIGH;

volatile int T120count;


Ubidots client(token, MQTTCLIENTNAME);
Ticker flipper;
Ticker indicationFlipper;



/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  client.wifiConnection(ssid, password);
  client.begin(callback);
  client.getValue(tempVarId);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(indicationPin,OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), IRQcounter, FALLING);
  }

void loop() {
    if(!uploaded)
    {
      uploadData();
    }

    checkConnection();

   delay(50);
   
  }

   void uploadData()
   {

     if(!client.connected()){
        client.reconnect();
        
     }

//     client.add("Temp", x); //Insert your variable Labels and the value to be sent
//     client.ubidotsPublish("UNO");
//     
//     client.add("Count", y); //Insert your variable Labels and the value to be sent
     client.ubidotsPublish("UNO");
     client.loop();
     uploaded = HIGH;
    
   }

   void IRQcounter() {
      client.setNewValue();
      digitalWrite(LED_BUILTIN, !client.connected());
      if (state)
      {
        bool falseTrg = LOW;
        long lastMilli = millis();
        while(millis()-lastMilli < 400)
        {
          falseTrg = digitalRead(interruptPin)  == 1;
          
        }

        if(!falseTrg)
        {
          T120count++;
          int result = T120count;
          client.add("Temp", T120count);
          Serial.print(F("Counted = "));
          Serial.println(result);
          state = LOW;
          uploaded = LOW;
          digitalWrite(indicationPin, HIGH);
          flipper.attach(30, flip);
          indicationFlipper.attach(1,indicationFlip);
        }
      }
  }

    void indicationFlip()
    {
      digitalWrite(indicationPin, LOW);
      indicationFlipper.detach();
    }
    
    void flip()
    {
    Serial.println("Now interrupt enabled");
    state = HIGH;
    flipper.detach();
  
    }

    void startUp()
    {
      
      
    }

  void checkConnection()
  {
    if (uploaded)
    {
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (!uploaded)
    {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    
    
    
  }


  
