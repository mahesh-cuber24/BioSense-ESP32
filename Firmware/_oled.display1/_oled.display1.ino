#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(
  U8G2_R0, 5, 27, 14 
);

void setup() {
  u8g2.begin();
  u8g2.clearBuffer();                       
  u8g2.setFont(u8g2_font_ncenB08_tr);       
  u8g2.drawStr(0, 20, "Hi ESP32"); 
  u8g2.sendBuffer();                        
}

void loop() {
}
