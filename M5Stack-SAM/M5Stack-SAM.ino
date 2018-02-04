#include <M5Stack.h>
#include "EEPROM.h"
#include <Wire.h>
#include "SimpleBeacon.h"

/* 
 * To let the Menu not grow to fast, both "Weather" Apps, 
 * appDHT12 and appBME280 use the same Menu Index.
 * If you like appDHT12, use this define
 * #define WEATHER_SENSOR WS_DHT12
 * else if you like appBME280, use this define
 * #define WEATHER_SENSOR WS_BME280
 */
#define WEATHER_SENSOR WS_BME280

#if defined(WS_DHT12)
  #include "utility/DHT12.h"
  DHT12 dht12;

#elif defined(WS_BME280)
  #include <Adafruit_Sensor.h>
  #include <Adafruit_BME280.h>

  #define SEALEVELPRESSURE_HPA (1013.25)
  Adafruit_BME280 bme280;
  bool status;
#endif

SimpleBeacon ble;


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
  
  #if defined(WS_BME280)
    status = bme280.begin(0x76);
  #endif
  
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
  
  
}

void loop() {
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




