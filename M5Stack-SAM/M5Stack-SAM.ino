#include <M5Stack.h>
#include <Wire.h>

#include "EEPROM.h"
#include "utility/DHT12.h"
#include "SimpleBeacon.h"
#include "qrcode.h"
#include "SerialCommand.h"

SimpleBeacon ble;
DHT12 dht12;

SerialCommand sCmd;

#define TFT_GREY 0x5AEB
#define TFT_BROWN 0x38E0

#define TFT_W 320
#define TFT_H 240

#define EEPROM_SIZE 64

unsigned int sys_menucolor;
unsigned int sys_windowcolor;
unsigned int sys_menutextcolor;

byte menuidx = 0;
byte menuidxmin = 0;
byte menuidxmax = 3;
byte menulock = 0;
boolean menuIsMenu = HIGH;

unsigned long tmp_tmr = 0;

void setup(void) {
  Serial.begin(115200);

  if (!EEPROM.begin(EEPROM_SIZE))
  {
    Serial.println("failed to initialise EEPROM");
    while(HIGH);
  }


  M5.begin();
  Wire.begin();

  M5.lcd.setBrightness(byte(EEPROM.read(0)));

  sys_menutextcolor = TFT_WHITE;
  sys_menucolor = setrgb(0,0,128);
  sys_windowcolor = TFT_GREY;

  menuUpdate(menuidx, menulock);

  sCmd.addCommand("eddystoneurl",    rcmdEddystoneURL);  
  sCmd.addCommand("eddystonetlm",    rcmdEddystoneTLM);  
  sCmd.addCommand("ibeacon",    rcmdIBeacon);  
  sCmd.addCommand("sleep",    rcmdSleep);  
  sCmd.addCommand("bright",    rcmdBright);  
  sCmd.addCommand("clr",    rcmdClr);
  sCmd.addCommand("qrc",    rcmdQRC);
  sCmd.setDefaultHandler(rcmdDef);

}

void loop() {
  sCmd.readSerial();
  if(M5.BtnA.wasPressed()) {
    if(menuidx>menuidxmin)menuidx--;
    menuUpdate(menuidx, menulock);
  }
  if(M5.BtnC.wasPressed()) {
    if(menuidx<menuidxmax)menuidx++;
    menuUpdate(menuidx, menulock);
  }
  if(M5.BtnB.wasPressed()) {
    if(menuIsMenu){
      menulock = menuidx;
      menuidx = 0;
      menuUpdate(menuidx, menulock);
    }else{
      menuRunApp(menuidx, menulock);
    }
  }
  M5.update();
}




