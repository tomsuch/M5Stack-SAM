int square(int x) {  // function declared and implemented
    return x*x;
}

String getSTAMac() {
  uint8_t baseMac[6];
  esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
  char baseMacChr[18] = {0};
  sprintf(baseMacChr, "%02X:%02X:%02X:%02X:%02X:%02X", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);
  return String(baseMacChr);
}

void rcmdWiFiScan(){
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    Serial.println(F("scan start"));
    int n = WiFi.scanNetworks();
    Serial.println(F("scan done"));
    if (n == 0) {
        Serial.println(F("no networks found"));
    } else {
        Serial.print(n);
        Serial.println(F(" networks found"));
        for (int i = 0; i < n; ++i) {
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
        }
    }
    Serial.println("");
}

void rcmdIICScan(){
  byte error, address;
  int nDevices;

  Serial.println(F("Scanning..."));

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print(F("I2C device found at address 0x"));
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print(F("Unknown error at address 0x"));
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println(F("No I2C devices found\n"));
  else
    Serial.println(F("done\n"));  
}

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
              Serial.println(F("OK"));
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
            Serial.println(F("OK"));
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

