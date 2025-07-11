#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <U8g2lib.h>
#include <SPI.h>

U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(
  U8G2_R0, 5, 27, 14 
);

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);     
  mlx.begin();             
  u8g2.begin();            
}

void loop() {
  float tempObj = mlx.readObjectTempC();  
  float tempAmb = mlx.readAmbientTempC(); 
  Serial.printf("Object: %.2f°C | Ambient: %.2f°C\n", tempObj, tempAmb);
  char objStr[25];
  char ambStr[25];
  sprintf(objStr, "Object: %.2f C", tempObj);
  sprintf(ambStr, "Ambient: %.2f C", tempAmb);

  // Display on OLED
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 20, "MLX90614 Sensor");
  u8g2.drawStr(0, 45, objStr);
  u8g2.drawStr(0, 60, ambStr);
  u8g2.sendBuffer();

  delay(1000);  
}
