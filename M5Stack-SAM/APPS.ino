
void appGY521(){
  menuDrawMenu(F("GY-521"),F(""),F("ESC"),F(""),sys_menucolor,sys_windowcolor,sys_menutextcolor);
  const int MPU=0x68; 
  int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ,axout,ayout,azout,gxout, gyout, gzout;
  long ax, ay, az, gx, gy, gz;
  int sidx = 0;
  int scount = 100;
  float _angle_x, angle_x, _angle_y, angle_y;
  const float pi = 3.141592;
  menuidx = 1;
  menulock = 0;
  M5.Lcd.setTextColor(sys_menutextcolor,sys_windowcolor);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  while(M5.BtnB.wasPressed()){
    M5.update();
  }  
  while(!M5.BtnB.wasPressed()){
    if(sidx <= scount){
      Wire.beginTransmission(MPU);
      Wire.write(0x3B);  
      Wire.endTransmission(false);
      Wire.requestFrom(MPU,12,true);  
      AcX=Wire.read()<<8|Wire.read();    
      AcY=Wire.read()<<8|Wire.read();  
      AcZ=Wire.read()<<8|Wire.read();  
      GyX=Wire.read()<<8|Wire.read();  
      GyY=Wire.read()<<8|Wire.read();  
      GyZ=Wire.read()<<8|Wire.read();
      ax = ax + AcX;  
      ay = ay + AcY;  
      az = az + AcZ;
      gx = gx + GyX;  
      gy = gy + GyY;  
      gz = gz + GyZ;  
      sidx++;
    }else{
      sidx = 0;
      axout = ax/scount;
      ayout = ay/scount;
      azout = az/scount;
      gxout = gx/scount;
      gyout = gy/scount;
      gzout = gz/scount;
      ax = 0;
      ay = 0;
      az = 0;
      gx = 0;
      gy = 0;
      gz = 0;
      angle_x = atan2(axout, sqrt(square(ayout) + square(azout))      )/(pi/180);
      angle_y = atan2(ayout, sqrt(square(axout) + square(azout))      )/(pi/180);
      char buffer[24];
      sprintf(buffer, "ANGLE X:  % 5.1f   ", angle_x);
      M5.Lcd.drawString(buffer,40,80,4);
      sprintf(buffer, "ANGLE Y:  % 5.1f   ", angle_y);
      M5.Lcd.drawString(buffer,40,120,4);
    }
    M5.update();
  }
  M5.Lcd.fillScreen(TFT_BLACK);
  menuUpdate(menuidx, menulock);  
}

void appSysInfo(){
  menuDrawMenu(F("M5 SYSTEM INFO"),F(""),F("ESC"),F(""),sys_menucolor,sys_windowcolor,sys_menutextcolor);
  menuidx = 2;
  menulock = 0;
  while(M5.BtnB.wasPressed()){
    M5.update();
  }
  uint8_t chipRev = ESP.getChipRevision();
  uint8_t cpuSpeed = ESP.getCpuFreqMHz();
  uint32_t flashSize = ESP.getFlashChipSize();
  uint32_t flashSpeed = ESP.getFlashChipSpeed();
  const char * sdkVer = ESP.getSdkVersion();
  String wifiSTAMAC = getSTAMac();
  
  M5.Lcd.drawString(F("CPU_FREQ:"),10,40,2);
  M5.Lcd.drawNumber(cpuSpeed, 120, 40, 2);
  
  M5.Lcd.drawString(F("CHIP_REV:"),10,60,2);
  M5.Lcd.drawNumber(chipRev, 120, 60, 2);
    
  M5.Lcd.drawString(F("FLASH_SIZE:"),10,80,2);
  M5.Lcd.drawNumber(flashSize, 120, 80, 2);

  M5.Lcd.drawString(F("FLASH_SPEED:"),10,100,2);
  M5.Lcd.drawNumber(flashSpeed, 120, 100, 2);

  M5.Lcd.drawString(F("SDK_VERSION:"),10,120,2);
  M5.Lcd.drawString(sdkVer,120,120,2);

  M5.Lcd.drawString(F("WIFI_STA_MAC:"),10,140,2);
  M5.Lcd.drawString(wifiSTAMAC,120,140,2);
    
  while(!M5.BtnB.wasPressed()){
    M5.update();
  }
  menuUpdate(menuidx, menulock);
}
void appSerialBridge(byte inSpdIdx, boolean inRun){
  HardwareSerial Serial2 = HardwareSerial(2);
  byte spdIdx = 0;
  int8_t spdLast = -1;
  unsigned long spdCfg = 9600;
  boolean spRun = LOW;
  boolean spLast = LOW;
  spdIdx = inSpdIdx;
  spRun = inRun;
  menuDrawMenu(F("SERIAL BRIDGE"),F("SPD"),F("ESC"),F("ON/OFF"),sys_menucolor,sys_windowcolor,sys_menutextcolor);
  M5.Lcd.drawCentreString(F("PORT 0"),TFT_W/2,40,2);
  menuidx = 1;
  menulock = 0;
  while(M5.BtnB.wasPressed()){
    M5.update();
  }  
  while(!M5.BtnB.wasPressed()){
    M5.update();
    if(spdIdx > 3){
      spdIdx = 0;
    }
    if(spdLast != spdIdx){
      spdLast = spdIdx;
      if(spdLast == 0){
        menuWindowClr(sys_windowcolor);
        spdCfg = 9600;
        M5.Lcd.drawCentreString(F("UART 2"),TFT_W/2,40,2);
        M5.Lcd.drawString(F("SPEED"),20,100,2);
        M5.Lcd.drawNumber(spdCfg, 100, 80, 6);
        M5.Lcd.drawString(F("STATE"),20,160,2);
        M5.Lcd.drawNumber(spLast, 100, 140, 6);
      }
      if(spdLast == 1){
        menuWindowClr(sys_windowcolor);
        spdCfg = 19200;
        M5.Lcd.drawCentreString(F("UART 2"),TFT_W/2,40,2);
        M5.Lcd.drawString(F("SPEED"),20,100,2);
        M5.Lcd.drawNumber(spdCfg, 100, 80, 6);
        M5.Lcd.drawString(F("STATE"),20,160,2);
        M5.Lcd.drawNumber(spLast, 100, 140, 6);
      }
      if(spdLast == 2){
        menuWindowClr(sys_windowcolor);
        spdCfg = 57600;
        M5.Lcd.drawCentreString(F("UART 2"),TFT_W/2,40,2);
        M5.Lcd.drawString(F("SPEED"),20,100,2);
        M5.Lcd.drawNumber(spdCfg, 100, 80, 6);
        M5.Lcd.drawString(F("STATE"),20,160,2);
        M5.Lcd.drawNumber(spLast, 100, 140, 6);
      }
      if(spdLast == 3){
        menuWindowClr(sys_windowcolor);
        spdCfg = 115200;
        M5.Lcd.drawCentreString(F("UART 2"),TFT_W/2,40,2);
        M5.Lcd.drawString(F("SPEED"),20,100,2);
        M5.Lcd.drawNumber(spdCfg, 100, 80, 6);
        M5.Lcd.drawString(F("STATE"),20,160,2);
        M5.Lcd.drawNumber(spLast, 100, 140, 6);
      }
    }
    if(M5.BtnA.wasPressed()){
      spdIdx++;
    }
    if(M5.BtnC.wasPressed()){
      if(spRun){
        spRun = LOW;
      }else{
        spRun = HIGH;
      }
    }
    if(spRun != spLast){
      spLast = spRun;
      menuWindowClr(sys_windowcolor);
      M5.Lcd.drawCentreString(F("UART 2"),TFT_W/2,40,2);
      M5.Lcd.drawString(F("SPEED"),20,100,2);
      M5.Lcd.drawNumber(spdCfg, 100, 80, 6);
      M5.Lcd.drawString(F("STATE"),20,160,2);
      M5.Lcd.drawNumber(spLast, 100, 140, 6);
      if(spLast){
        Serial.begin(spdCfg);
        Serial2.begin(spdCfg);
        delay(100);        
      }else{
        Serial.end();
        Serial2.end();
        delay(100);        
      }
    }
    if(spLast){
        if (Serial.available()) {
          Serial2.write(Serial.read());
        }

        if (Serial2.available()) {
          Serial.write(Serial2.read());
        }
    }
  }
  Serial.end();
  Serial2.end();
  Serial.begin(115200);
  menuUpdate(menuidx, menulock);    
}

void appQRPrint(){
  menuidx = 1;
  menulock = 0;
  while(M5.BtnB.wasPressed()){
    M5.update();
  }  
  QRPrint("TomSuch|Prague CZ|www.m5stack.com|tomsuch@tomsuch.net");
  while(!M5.BtnB.wasPressed()){
    M5.update();
  }
  M5.Lcd.fillScreen(TFT_BLACK);
  menuUpdate(menuidx, menulock);  
}

void appBLEBaecon(){
  byte beaconIdx = 0;
  menuDrawMenu(F("BLE BEACON SIMULATOR"),F(""),F("ESC"),F(""),sys_menucolor,sys_windowcolor,sys_menutextcolor);
  M5.Lcd.drawCentreString(F("RUNNING"),TFT_W/2,TFT_H/2,2);
  menuidx = 1;
  menulock = 0;
  while(M5.BtnB.wasPressed()){
    M5.update();
  }  
  while(!M5.BtnB.wasPressed()){
    M5.update();
    if(millis()-tmp_tmr > 300){
      tmp_tmr = millis();
      if(beaconIdx==4){
        beaconIdx = 0;
      }      
      if(beaconIdx==0){
        ble.iBeacon(10,20,50);
      }
      if(beaconIdx==1){
        ble.EddystoneTLM(2048,512,100,1024);
      }
      if(beaconIdx==2){
        ble.EddystoneURIPlain(1,"brmlab.cz",1);
      }
      if(beaconIdx==3){
        ble.AltBeacon();
      }
      beaconIdx++;
    }
  }
  ble.end();
  menuUpdate(menuidx, menulock);  
}


void appDHT12(){
  menuDrawMenu(F("DHT12"),F(""),F("ESC"),F(""),sys_menucolor,sys_windowcolor,sys_menutextcolor);
  M5.Lcd.drawString(F("TEMPERATURE"),30,80,2);
  M5.Lcd.drawString(F("*C"),250,80,2);
  M5.Lcd.drawString(F("HUMIDITY"),30,140,2);
  M5.Lcd.drawString(F("%RH"),250,140,2);
  menuidx = 1;
  menulock = 0;
  M5.Lcd.setTextColor(sys_menutextcolor, sys_windowcolor);
  while(M5.BtnB.wasPressed()){
    M5.update();
  }  
  while(!M5.BtnB.wasPressed()){
    M5.update();
    if(millis()-tmp_tmr > 1000){
      tmp_tmr = millis();
      float tmp_teplota = dht12.readTemperature();
      float tmp_vlhkost = dht12.readHumidity();
      //menuWindowClr(sys_windowcolor);
      M5.Lcd.drawFloat(tmp_teplota, 1, 140, 60, 6);
      M5.Lcd.drawFloat(tmp_vlhkost, 1, 140, 120, 6);
    }
  }
  menuUpdate(menuidx, menulock);  
}

void appStopky(){
  boolean tmp_run = false;
  float tmp_sec = 0;
  unsigned int tmp_min = 0;
  menuDrawMenu(F("TIME MEASUREMENT"),F("S/S"),F("ESC"),F("RES"),sys_menucolor,sys_windowcolor,sys_menutextcolor);
  M5.Lcd.drawString(F("MIN"),10,120,2);
  M5.Lcd.drawString(F("SEC"),140,120,2);
  M5.Lcd.drawFloat(tmp_sec, 1, 180, 100, 6);
  M5.Lcd.drawNumber(tmp_min, 50, 100, 6);
  menuidx = 1;
  menulock = 0;
  M5.Lcd.setTextColor(sys_menutextcolor, sys_windowcolor);
  while(M5.BtnB.wasPressed()){
    M5.update();
  }  
  while(!M5.BtnB.wasPressed()){
    M5.update();
    if(M5.BtnC.wasPressed()){
      tmp_sec = 0;
      tmp_min = 0;      
      menuWindowClr(sys_windowcolor);
      M5.Lcd.drawString(F("MIN"),10,120,2);
      M5.Lcd.drawString(F("SEC"),140,120,2);
      M5.Lcd.drawFloat(tmp_sec, 1, 180, 100, 6);
      M5.Lcd.drawNumber(tmp_min, 50, 100, 6);
    }
    if(tmp_run){
      if(M5.BtnA.wasPressed()){
        tmp_run = LOW;
      }
      if(millis()-tmp_tmr > 100){
        tmp_tmr = millis();
        tmp_sec = tmp_sec + 0.1;
        if(tmp_sec > 59.9){
          tmp_sec = 0;
          tmp_min++;
          menuWindowClr(sys_windowcolor);
          M5.Lcd.drawString(F("MIN"),10,120,2);
          M5.Lcd.drawString(F("SEC"),140,120,2);
          M5.Lcd.drawFloat(tmp_sec, 1, 180, 100, 6);
          M5.Lcd.drawNumber(tmp_min, 50, 100, 6);
        }
        M5.Lcd.drawFloat(tmp_sec, 1, 180, 100, 6);
        M5.Lcd.drawNumber(tmp_min, 50, 100, 6);
      }      
    }else{
      if(M5.BtnA.wasPressed()){
        //tmp_sec = 0;
        //tmp_min = 0;
        tmp_run = HIGH;
      }
    }
  }
  menuUpdate(menuidx, menulock);  
}

void appIICScanner(){
  byte error, address;
  int nDevices;
  byte ridx = 0;
  byte lidx = 0;
  menuidx = 1;
  menulock = 0;
  boolean scanrun = HIGH;
  
  menuDrawMenu(F("I2C SCANNER"),F("SCAN"),F("ESC"),F(""),sys_menucolor,sys_windowcolor,sys_menutextcolor);
  M5.Lcd.setTextColor(sys_menutextcolor, sys_windowcolor);

  while(M5.BtnB.wasPressed()){
    M5.update();
  }
    
  while(!M5.BtnB.wasPressed()){
    if(scanrun==HIGH){
      scanrun = LOW;
      nDevices = 0;
      for(address = 1; address < 127; address++ ){
        ridx++;
        if(ridx==17){
          ridx = 1;
          lidx++;
        }
        Wire.beginTransmission(address);
        error = Wire.endTransmission();    
        if (error == 0){
          M5.Lcd.drawString(String(address,HEX),0+(ridx*18),45+(lidx*20),2);
          nDevices++;
        }else if (error==4){
          M5.Lcd.drawString(F("ER"),0+(ridx*18),45+(lidx*20),2);
        }else{
          M5.Lcd.drawString(F("--"),0+(ridx*18),45+(lidx*20),2);
        }
      }
      M5.update();
    }else{
      if(M5.BtnA.wasPressed()){
        ridx = 0;
        lidx = 0;
        scanrun = HIGH;
      }
      M5.update();
    }
  }  
  menuUpdate(menuidx, menulock);  
}

void appCfgBrigthness(){
  menuidx = 3;
  menulock = 0;
  byte tmp_brigth = byte(EEPROM.read(0));
  byte tmp_lbrigth = 0;
  
  menuDrawMenu(F("DISPLAY BRIGHTNESS"),F("-"),F("OK"),F("+"),sys_menucolor,sys_windowcolor,sys_menutextcolor);
  M5.Lcd.setTextColor(sys_menutextcolor, sys_windowcolor);

  while(M5.BtnB.wasPressed()){
    M5.update();
  }  

  while(!M5.BtnB.wasPressed()){
    if(M5.BtnA.wasPressed() and tmp_brigth >= 16){
      tmp_brigth = tmp_brigth - 16;
    }
    if(M5.BtnC.wasPressed() and tmp_brigth <= 239){
      tmp_brigth = tmp_brigth + 16;
    }
    if(tmp_lbrigth != tmp_brigth){
      tmp_lbrigth = tmp_brigth;
      EEPROM.write(0,tmp_lbrigth);
      EEPROM.commit();
      M5.lcd.setBrightness(byte(EEPROM.read(0)));
      menuDrawMenu(F("DISPLAY BRIGHTNESS"),F("-"),F("OK"),F("+"),sys_menucolor,sys_windowcolor,sys_menutextcolor);
      M5.Lcd.setTextColor(sys_menutextcolor, sys_windowcolor);
      M5.Lcd.drawNumber(byte(EEPROM.read(0)), 120 , 90, 6);
    }
    M5.update();
  }

  menuUpdate(menuidx, menulock);      
}


