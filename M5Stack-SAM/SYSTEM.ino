void QRPrint(String inStr) {  
  M5.Lcd.setTextColor(TFT_BLACK, TFT_WHITE);
  M5.Lcd.fillScreen(TFT_WHITE);

  uint32_t dt = millis();
  QRCode qrcode;
  uint8_t version = 6;
  uint8_t qrcodeData[qrcode_getBufferSize(version)];
  qrcode_initText(&qrcode, qrcodeData, version, 0, inStr.c_str());
  dt = millis() - dt;

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

