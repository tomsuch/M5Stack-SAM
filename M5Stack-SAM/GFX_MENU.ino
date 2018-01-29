void windowPrintInfo(unsigned int intextcolor){
  M5.Lcd.setTextColor(intextcolor);  
  M5.Lcd.drawCentreString(F("TomSuch@2018"),TFT_W/2,TFT_H/2,2);  
}

void windowPrintInfoText(String intext, unsigned int intextcolor){
  M5.Lcd.setTextColor(intextcolor);  
  M5.Lcd.drawCentreString(intext,TFT_W/2,TFT_H/2,2);  
}

void menuWindowClr(unsigned int incolor){
  M5.Lcd.fillRoundRect(0,32,TFT_W,TFT_H-32-32,3,incolor);
}

void menuDrawMenu(String inmenutxt, String inbtnatxt, String inbtnbtxt, String inbtnctxt, unsigned int inmenucolor, unsigned int inwindowcolor, unsigned int intxtcolor){
  M5.Lcd.fillRoundRect(31,TFT_H-28,60,28,3,inmenucolor);  
  M5.Lcd.fillRoundRect(126,TFT_H-28,60,28,3,inmenucolor);  
  M5.Lcd.fillRoundRect(221,TFT_H-28,60,28,3,inmenucolor);  
  M5.Lcd.fillRoundRect(0,0,TFT_W,28,3,inmenucolor);  
  M5.Lcd.fillRoundRect(0,32,TFT_W,TFT_H-32-32,3,inwindowcolor);  
    
  M5.Lcd.setTextColor(intxtcolor);
  M5.Lcd.drawCentreString(inmenutxt,TFT_W/2,6,2);

  M5.Lcd.drawCentreString(inbtnatxt,31+30,TFT_H-28+6,2);
  M5.Lcd.drawCentreString(inbtnbtxt,126+30,TFT_H-28+6,2);
  M5.Lcd.drawCentreString(inbtnctxt,221+30,TFT_H-28+6,2);  
}

void menuUpdate(byte inmenuidx, byte inmenulock){
  switch (inmenulock) {
    case 0:
      menuTopLevel(inmenuidx);
      break;
    case 1:
      menuAplikaceLevel(inmenuidx);
      break;
    case 2:
      menuSystemLevel(inmenuidx);
      break;
    case 3:
      menuNastaveniLevel(inmenuidx);
      break;
    default:
      Serial.println();
  }  
}

void menuTopLevel(byte inmenuidx){
  menuidxmin = 0;
  menuidxmax = 3;
  switch (inmenuidx) {
    case 0:
      menuIsMenu = HIGH;
      menuDrawMenu(F("MAIN MENU"),F("<"),F("OK"),F(">"),sys_menucolor,sys_windowcolor,sys_menutextcolor);
      windowPrintInfo(sys_menutextcolor);
      break;
    case 1:
      menuIsMenu = HIGH;
      menuDrawMenu(F("APPLICATIONS"),F("<"),F("OK"),F(">"),sys_menucolor,sys_windowcolor,sys_menutextcolor);
      break;
    case 2:
      menuIsMenu = HIGH;
      menuDrawMenu(F("SYSTEM"),F("<"),F("OK"),F(">"),sys_menucolor,sys_windowcolor,sys_menutextcolor);
      break;
    case 3:
      menuIsMenu = HIGH;
      menuDrawMenu(F("CONFIGURATION"),F("<"),F("OK"),F(">"),sys_menucolor,sys_windowcolor,sys_menutextcolor);
      break;
    default:
      Serial.println();
  }    
}

void menuNastaveniLevel(byte inmenuidx){
  menuidxmin = 0;
  menuidxmax = 1;
  switch (inmenuidx) {
    case 0:
      menuIsMenu = LOW;
      menuWindowClr(sys_windowcolor);
      windowPrintInfoText(F("DISPLAY - BRIGHTNESS"),sys_menutextcolor);
      break;
    case 1:
      menuIsMenu = LOW;
      menuWindowClr(sys_windowcolor);
      windowPrintInfoText(F("RETURN"),sys_menutextcolor);
      break;
    default:
      Serial.println();
  }    
}

void menuSystemLevel(byte inmenuidx){
  menuidxmin = 0;
  menuidxmax = 1;
  switch (inmenuidx) {
    case 0:
      menuIsMenu = LOW;
      menuWindowClr(sys_windowcolor);
      windowPrintInfoText(F("SLEEP/CHARGING"),sys_menutextcolor);
      break;
    case 1:
      menuIsMenu = LOW;
      menuWindowClr(sys_windowcolor);
      windowPrintInfoText(F("RETURN"),sys_menutextcolor);
      break;
    default:
      Serial.println();
  }    
}

void menuAplikaceLevel(byte inmenuidx){
  menuidxmin = 0;
  menuidxmax = 4;
  switch (inmenuidx) {
    case 0:
      menuIsMenu = LOW;
      menuWindowClr(sys_windowcolor);
      windowPrintInfoText(F("DHT12"),sys_menutextcolor);
      break;
    case 1:
      menuIsMenu = LOW;
      menuWindowClr(sys_windowcolor);
      windowPrintInfoText(F("TIME MEASUREMENT"),sys_menutextcolor);
      break;
    case 2:
      menuIsMenu = LOW;
      menuWindowClr(sys_windowcolor);
      windowPrintInfoText(F("I2C Scanner"),sys_menutextcolor);
      break;
    case 3:
      menuIsMenu = LOW;
      menuWindowClr(sys_windowcolor);
      windowPrintInfoText(F("BLE Beacon SIMULATOR"),sys_menutextcolor);
      break;
    case 4:
      menuIsMenu = LOW;
      menuWindowClr(sys_windowcolor);
      windowPrintInfoText(F("RETURN"),sys_menutextcolor);
      break;
    default:
      Serial.println();
  }    
}


void menuRunApp(byte inmenuidx, byte inmenulock){
  if(inmenulock==2 and inmenuidx==0){
      M5.setWakeupButton(BUTTON_B_PIN);
      M5.powerOFF();        
  }
  if(inmenulock==2 and inmenuidx==1){
      menuidx = 2;
      menulock = 0;
      menuUpdate(menuidx, menulock);        
  }

  if(inmenulock==3 and inmenuidx==0){
    appCfgBrigthness();
  }
  if(inmenulock==3 and inmenuidx==1){
      menuidx = 3;
      menulock = 0;
      menuUpdate(menuidx, menulock);        
  }

  if(inmenulock==1 and inmenuidx==0){
    appDHT12();
  }
  if(inmenulock==1 and inmenuidx==1){
    appStopky();
  }
  if(inmenulock==1 and inmenuidx==2){
    appIICScanner();
  }
  if(inmenulock==1 and inmenuidx==3){
    appBLEBaecon();
  }
  if(inmenulock==1 and inmenuidx==4){
      menuidx = 1;
      menulock = 0;
      menuUpdate(menuidx, menulock);        
  }
}





