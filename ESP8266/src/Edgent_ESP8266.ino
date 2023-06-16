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
#define BLYNK_TEMPLATE_ID "TMPL2MJWdUOx8"
#define BLYNK_TEMPLATE_NAME "Talking Wall"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

//#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

//#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

#define volUpPin D0
#define volDownPin D1
#define pPin D6

int vol = 0;

void playPause(){
  digitalWrite(pPin, LOW);
  delay(500);
  digitalWrite(pPin, HIGH);
}

void resetVolMax(){
  Serial.println("increasing now");
  digitalWrite(volUpPin, LOW);
  delay(6000);
  digitalWrite(volUpPin, HIGH);
}

void resetVolMin(){
  Serial.println("reseting volume");
  digitalWrite(volDownPin, LOW);
  delay(6000);
  digitalWrite(volDownPin, HIGH);
}
void volUp(){
  digitalWrite(volUpPin, LOW);
  delay(200);
  digitalWrite(volUpPin, HIGH);
}
void volDown(){
  digitalWrite(volDownPin, LOW);
  delay(200);
  digitalWrite(volDownPin, HIGH);
}

void setVol(int set){
  if(set == vol){
    return;
  }
  if (vol < set){
    while(vol < set){
      vol++;
      volUp();
    }
    return;
  }
  else {
    while(vol > set){
      vol--;
      volDown();
    }
    return;
  }
  
}



void setup()
{
  pinMode(pPin, OUTPUT);
  pinMode(volDownPin, OUTPUT);
  pinMode(volUpPin, OUTPUT);
  digitalWrite(pPin, HIGH);
  digitalWrite(volDownPin, HIGH);
  digitalWrite(volUpPin, HIGH);
  resetVolMin();
  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}

BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V1);
}

BLYNK_WRITE(V0) {
  int virtual_pin_value = param.asInt();
  if (virtual_pin_value == 1){
    playPause(); //toggle the play mode
  }
}

BLYNK_WRITE(V1){
  int volume = param.asInt(); // volume value 0-30
  setVol(volume);
}

