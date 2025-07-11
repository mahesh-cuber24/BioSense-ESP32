#include <U8g2lib.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>


U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(
  U8G2_R0, 5,  27,  14
);

// DHT22 setup
#define DHTPIN 4        
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  u8g2.begin();
}

void loop() {
  // Read temperature and humidity
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if reading failed
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }


  Serial.printf("Temp: %.1f°C, Humidity: %.1f%%\n", t, h);

  // Display on OLED
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  
  u8g2.drawStr(0, 15, "DHT22 Sensor");
  
  char tempStr[20];
  sprintf(tempStr, "Temp: %.1f C", t);
  u8g2.drawStr(0, 35, tempStr);
  
  char humStr[20];
  sprintf(humStr, "Humidity: %.1f %%", h);
  u8g2.drawStr(0, 55, humStr);

  u8g2.sendBuffer();

  delay(2000); 
}
