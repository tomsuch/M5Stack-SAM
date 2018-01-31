void rcmdQRC(){
  int aNumber;
  char *arg;
  arg = sCmd.next();
  if (arg != NULL) {
   QRPrint(arg); 
  }
}

void rcmdSleep(){
  M5.setWakeupButton(BUTTON_B_PIN);
  M5.powerOFF(); 
}

void rcmdBright(){
  int aNumber;
  char *arg;
  unsigned int tmpval;
  
  arg = sCmd.next();
  if (arg != NULL) {
    tmpval = atoi(arg);
    if(tmpval >= 0 and tmpval <= 255){
      EEPROM.write(0,tmpval);
      EEPROM.commit();
      M5.lcd.setBrightness(byte(EEPROM.read(0)));
    }
  }
}

void rcmdIBeacon(){
  int aNumber;
  char *arg;

  unsigned int tmpmajor;
  unsigned int tmpminor;
  byte tmppwr;
  
  arg = sCmd.next();
  if (arg != NULL) {
    tmpmajor = atoi(arg);
    if(tmpmajor >= 0 and tmpmajor <= 65535){
      arg = sCmd.next();
      if (arg != NULL) {
        tmpminor = atoi(arg);
        if(tmpminor >= 0 and tmpminor <= 65535){
          arg = sCmd.next();
          if (arg != NULL) {
            tmppwr = atoi(arg);
            if(tmppwr >= 0 and tmppwr <= 255){
              ble.iBeacon(tmpmajor,tmpminor,tmppwr);
              delay(100);
              ble.end();
              Serial.println("OK");
            }
          }
        }
      }
    }
  }
}

void rcmdEddystoneURL(){
  int aNumber;
  char *arg;

  unsigned int tmppref;
  unsigned int tmppwr;
    
  arg = sCmd.next();
  if (arg != NULL) {
    tmppref = atoi(arg);
    if(tmppref >= 0 and tmppref <= 3){
      arg = sCmd.next();
      if (arg != NULL) {
        tmppwr = atoi(arg);
        if(tmppwr >= 0 and tmppwr <= 255){
          arg = sCmd.next();
          if (arg != NULL) {
            ble.EddystoneURIPlain(tmppref,arg,tmppwr);
            delay(100);
            ble.end();
            Serial.println("OK");
          }
        }
      }
    }
  }
}

void rcmdEddystoneTLM(){
  int aNumber;
  char *arg;

  unsigned int tmpvolt;
  unsigned int tmptemp;
  unsigned long tmpcount;
  unsigned long tmptime;
  
  arg = sCmd.next();
  if (arg != NULL) {
    tmpvolt = atoi(arg);
    if(tmpvolt >= 0 and tmpvolt <= 65535){
      arg = sCmd.next();
      if (arg != NULL) {
        tmptemp = atoi(arg);
        if(tmptemp >= 0 and tmptemp <= 65535){
          arg = sCmd.next();
          if (arg != NULL) {
            tmpcount = atol(arg);
            if(tmpcount >= 0 and tmpcount <= 4294967295){
              arg = sCmd.next();
              if (arg != NULL) {
                tmptime = atol(arg);
                if(tmptime >= 0 and tmptime <= 4294967295){
                  ble.EddystoneTLM(tmpvolt,tmptemp,tmpcount,tmptime);
                  delay(100);
                  ble.end();
                  Serial.println("OK");                  
                }
              }
            }
          }
        }
      }
    }
  }
}


void rcmdClr() {
  menuidx = 0;
  menulock = 0;
  M5.Lcd.fillScreen(TFT_BLACK);
  menuUpdate(menuidx, menulock);  
}

void rcmdDef(const char *command) {
  Serial.println(F("ERROR"));
}

void QRPrint(String inStr) {  
  M5.Lcd.setTextColor(TFT_BLACK, TFT_WHITE);
  M5.Lcd.fillScreen(TFT_WHITE);

  QRCode qrcode;
  uint8_t version = 6;
  uint8_t qrcodeData[qrcode_getBufferSize(version)];
  qrcode_initText(&qrcode, qrcodeData, version, 0, inStr.c_str());

  uint8_t thickness = 220 / qrcode.size;
  uint16_t lineLength = qrcode.size * thickness;
  uint8_t xOffset = (320 - (lineLength)) / 2;
  uint8_t yOffset = (240 - (lineLength)) / 2;
  for (uint8_t y = 0; y < qrcode.size; y++) {
    for (uint8_t x = 0; x < qrcode.size; x++) {
      bool q = qrcode_getModule(&qrcode, x, y);
      if (q) {
        M5.Lcd.fillRect(x * thickness + xOffset, y * thickness + yOffset, thickness, thickness, TFT_BLACK);
      }
    }
  }
}

unsigned int setrgb(byte inred, byte ingrn, byte inblue){
  inred = map(inred,0,255,0,31);
  ingrn = map(ingrn,0,255,0,31);
  inblue = map(inblue,0,255,0,31);
  return inred << 11 | ingrn << 5 | inblue;
}

