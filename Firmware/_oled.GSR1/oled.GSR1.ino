#include <U8g2lib.h>
#include <SPI.h>
U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(
  U8G2_R0, 5, 27,  14 
);

// GSR sensor pin
#define GSR_PIN 34  

void setup() {
  Serial.begin(115200);
  u8g2.begin();
}

void loop() {
  int gsrValue = analogRead(GSR_PIN); 
  Serial.print("GSR Value: ");
  Serial.println(gsrValue);
  char buffer[20];
  sprintf(buffer, "Impedance: %d", gsrValue);

  // Display on OLED
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr); 
  u8g2.drawStr(0, 20, "GSR Sensor");
  u8g2.drawStr(0, 45, buffer);
  u8g2.sendBuffer();

  delay(500); 
}
