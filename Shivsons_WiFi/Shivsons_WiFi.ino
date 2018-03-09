

/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsMicroESP8266.h"
#include <SoftwareSerial.h>
#include <dummy.h>
#include <Ticker.h>



/****************************************
 * Define Constants
 ****************************************/
#define ssid  "shivsons"
#define password  "*vijay214"
#define tempVarId  "586996d57625425717591bc1"
#define token  "khD4jqMtp22gGSPXRPAg1yYMBEFc8Y"


const byte interruptPin = 4;
const byte indicationPin = 14;
volatile byte state = HIGH;
volatile byte rising = HIGH;
volatile byte uploaded = HIGH;

volatile int T120count;


Ubidots client(token);
Ticker flipper;
Ticker indicationFlipper;



/****************************************
 * Auxiliar Functions
 ****************************************/

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  client.wifiConnection(ssid, password);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(indicationPin,OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(interruptPin), ISR, CHANGE);
  }

void loop() {
    if(!uploaded)
    {
      uploadData();
    }

    checkConnection();

   delay(3000);
   
  }

   void uploadData()
   {
     Serial.println("upload Data Called");
     long value = -1;
     value = client.getValueUDP(tempVarId);
     if (value != 0)
     {
       T120count = T120count + value;
       client.add(tempVarId,T120count);
       uploaded = client.sendAll(false);
         if (uploaded)
         {
          T120count = 0;
         }
        
     }
   }
  void ISR ()
  {
    if (digitalRead(interruptPin) == HIGH)
    {
      risingOne();
    }
    else
    {
      fallingOne();
    }
  }


   void risingOne()

   {
        bool falseTrg = LOW;
        long lastMilli = millis();
        while(millis()-lastMilli < 400)
        {
          falseTrg = digitalRead(interruptPin)  == 0;
        }
        if(!falseTrg)
        {
           Serial.println("rising HIGH now");
          rising = HIGH;
        }
        
        
   }

   void fallingOne() {
      if (state && rising)
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
          state = LOW;
          rising = LOW;
          Serial.println("rising LOW now");
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
    if(WiFi.status() != WL_CONNECTED)
    {
      client.wifiConnection(ssid, password);
    }
    if (uploaded)
    {
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (!uploaded)
    {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    
    
    
  }


  
