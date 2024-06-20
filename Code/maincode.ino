/* Code Made By Harikesh OP*/
/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */

#include "DHT.h"
#define DHTPIN D3 
#define DHTTYPE DHT11
float h,t;
int ldr;

DHT dht(DHTPIN, DHTTYPE);
#define BLYNK_TEMPLATE_ID "TMPL3ro7ODe2I"
#define BLYNK_TEMPLATE_NAME "Home automation"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
BLYNK_WRITE(V0)
{
  int value = param.asInt();
  if(value){
      digitalWrite(D0, LOW);
    }
  else
    digitalWrite(D0, HIGH);
  }

BLYNK_WRITE(V1)
{
  int value = param.asInt();
  if(value){
      digitalWrite(D1, LOW);
    }
  else
    digitalWrite(D1, HIGH);
  }
BLYNK_WRITE(V2)
{
  int value = param.asInt();
  if(value){
      digitalWrite(D2, LOW);
    }
  else
    digitalWrite(D2, HIGH);
  }
BLYNK_WRITE(V3)
{
  int value = param.asInt();
  if(value){
      digitalWrite(D4, LOW);
    }
  else
    digitalWrite(D4, HIGH);
}
  BLYNK_WRITE(V4)
{
  int value = param.asInt();
  int outPut = map(value, 0, 100, 0, 255 );
  analogWrite(D8, outPut);
}

void temparatureData(){
  h = dht.readHumidity();
  t = dht.readTemperature();

  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);

  delay(500);
  }
void detectFlame(){
  int flame = digitalRead(D7);
  Serial.println(flame);
  Blynk.virtualWrite(V9, flame);
  if(flame == 0)
    Blynk.logEvent("Flame");
  }
void detectSmoke(){
  int smoke = digitalRead(D5);
  Serial.println(smoke);
  Blynk.virtualWrite(V8, smoke);
  if(smoke == 0)
    Blynk.logEvent("smoke_detected");
  }
void setup()
{
  Serial.begin(115200);
  delay(100);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D5, INPUT);
  pinMode(10, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
  pinMode(D8, OUTPUT);

  digitalWrite(D0, HIGH);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D8, LOW);
  dht.begin();
  

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
  temparatureData();
  detectFlame();
  detectSmoke();
  ldr = digitalRead(D6);
  Blynk.virtualWrite(V7, ldr);
  

}
/*Made by HARIKESH*/