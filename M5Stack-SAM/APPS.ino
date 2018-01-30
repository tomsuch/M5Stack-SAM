void appBLEBaecon(){
  byte beaconIdx = 0;
  menuDrawMenu(F("BLE BEACON SIMULATOR"),F(""),F("ESC"),F(""),sys_menucolor,sys_windowcolor,sys_menutextcolor);
  M5.Lcd.drawString(F("RUNNING"),120,90,2);
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


void appBME280(){
  menuDrawMenu(F("BME280"),F(""),F("ESC"),F(""),sys_menucolor,sys_windowcolor,sys_menutextcolor);
  M5.Lcd.drawString(F("TEMPERATURE"),30,60,2);
  M5.Lcd.drawString(F("°C"),250,60,2);
  M5.Lcd.drawString(F("HUMIDITY"),30,120,2);
  M5.Lcd.drawString(F("%RH"),250,120,2);
  M5.Lcd.drawString(F("PRESSURE"),30,180,2);
  M5.Lcd.drawString(F("hPa"),250,180,2);
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
      float tmp_temp = bme280.readTemperature();
      float tmp_humi = bme280.readHumidity();
      float tmp_pres = (bme280.readPressure()/100.0F);
      //menuWindowClr(sys_windowcolor);
      M5.Lcd.drawFloat(tmp_temp, 1, 140, 40, 6);
      M5.Lcd.drawFloat(tmp_humi, 1, 140, 100, 6);
      M5.Lcd.drawFloat(tmp_pres, 1, 140, 160, 6);
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
        tmp_sec = 0;
        tmp_min = 0;
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


