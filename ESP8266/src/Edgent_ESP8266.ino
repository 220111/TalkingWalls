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


void setup()
{
  Serial.begin(9600);
  delay(100);
  Serial.write(0xAA0200AC); // set playing state to STOP
  Serial.write(0xAA180101); // set looping mode to loop single
  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}

BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);  // will cause BLYNK_WRITE(V0) to be executed
  Blynk.syncVirtual(V1);  // will cause BLYNK_WRITE(V1) to be executed
}

BLYNK_WRITE(V0) {
  int virtual_pin_value = param.asInt();
  if (virtual_pin_value == 1){
    Serial.write(0xAA0200AC); // set playing state to PLAY
  }
  if (virtual_pin_value == 0){
    Serial.write(0xAA0200AD); // set playing state to PAUSE
  }
}

BLYNK_WRITE(V1){
  int volume = param.asInt(); // volume value 0-30
  int ret = 0xAA130100 + volume; // command to set volume + desired volume level
  Serial.write(ret); // send command
}

