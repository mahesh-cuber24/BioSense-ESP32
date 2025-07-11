// Sensors: MLX90614, MAX30102, DHT22, GSR
// Display: OLED (SSD1306 or SH1106 via SPI)
// Cloud: ThingSpeak Upload

#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <SPI.h>
#include <U8g2lib.h>
#include <Adafruit_MLX90614.h>
#include <MAX30105.h>
#include <heartRate.h>
#include <DHT.h>

// --------- Wi-Fi + ThingSpeak ---------
const char* ssid = "Your ssid";
const char* password = "your password";
const char* server = "http://api.thingspeak.com/update";
String apiKey = "Your apikey";
unsigned long channelID = 111111; // your channel ID 

// --------- Sensor Pins ----------
#define DHTPIN 4
#define DHTTYPE DHT22
#define GSR_PIN 34  // Analog input

// ---------- OLED ---------------
U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, 5, 27, 14);

// --------- Sensor Objects ----------
DHT dht(DHTPIN, DHTTYPE);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
MAX30105 maxSensor;

const byte RATE_SIZE = 4;
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;
float spo2 = 0;

// ------- SpO2 Variables ---------
#define BUFFER_SIZE 50
uint32_t irBuffer[BUFFER_SIZE];
uint32_t redBuffer[BUFFER_SIZE];

void setup() {
  Serial.begin(115200);
  Serial.println("Serial started");

  Wire.begin(21, 22);

  dht.begin();

  if (!mlx.begin()) {
    Serial.println("⚠ MLX90614 not found!");
  } else {
    Serial.println("MLX90614 initialized");
  }

  if (!maxSensor.begin(Wire)) {
    Serial.println("⚠ MAX30102 not found!");
  } else {
    Serial.println("MAX30102 initialized");
    maxSensor.setup();
    maxSensor.setPulseAmplitudeRed(0x3F);
    maxSensor.setPulseAmplitudeIR(0x3F);
  }

  u8g2.begin();
  Serial.println("OLED initialized");

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void loop() {
  Serial.println("\nReading sensors...");

  float tempDHT = dht.readTemperature();
  float humDHT = dht.readHumidity();
  float tempObj = mlx.readObjectTempC();
  float tempAmb = mlx.readAmbientTempC();
  int gsrValue = analogRead(GSR_PIN);

  Serial.printf("DHT22 → Temp: %.2f, Humidity: %.2f\n", tempDHT, humDHT);
  Serial.printf("MLX90614 → Object: %.2f°C, Ambient: %.2f°C\n", tempObj, tempAmb);
  Serial.printf("GSR Sensor → Value: %d\n", gsrValue);

  long irValue = maxSensor.getIR();
  Serial.printf("MAX30102 IR Value: %ld\n", irValue);

  bool isBeat = checkForBeat(irValue);

  if (isBeat) {
    long now = millis();
    long delta = now - lastBeat;
    lastBeat = now;

    beatsPerMinute = 60.0 / (delta / 1000.0);

    if (beatsPerMinute > 20 && beatsPerMinute < 255) {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;

      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }

  for (int i = 0; i < BUFFER_SIZE; i++) {
    int attempts = 0;
    while (!maxSensor.available() && attempts++ < 10) delay(5);
    redBuffer[i] = maxSensor.getRed();
    irBuffer[i] = maxSensor.getIR();
    maxSensor.nextSample();
  }

  long redAC = 0, irAC = 0;
  long redDC = 0, irDC = 0;

  for (int i = 0; i < BUFFER_SIZE; i++) {
    redDC += redBuffer[i];
    irDC += irBuffer[i];
  }
  redDC /= BUFFER_SIZE;
  irDC /= BUFFER_SIZE;

  for (int i = 0; i < BUFFER_SIZE; i++) {
    redAC += labs((long)redBuffer[i] - redDC);
    irAC += labs((long)irBuffer[i] - irDC);
  }

  float ratio = ((float)redAC / redDC) / ((float)irAC / irDC);
  spo2 = 110.0 - 25.0 * ratio;
  spo2 = constrain(spo2, 0, 100);

  Serial.printf("Heart Rate: %d bpm, SpO2: %.1f%%\n", beatAvg, spo2);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_tf);
  u8g2.setCursor(0, 12);
  u8g2.printf("T:%.1f H:%.1f", tempDHT, humDHT);
  u8g2.setCursor(0, 24);
  u8g2.printf("Obj:%.1f Amb:%.1f", tempObj, tempAmb);
  u8g2.setCursor(0, 36);
  u8g2.printf("GSR:%d", gsrValue);
  u8g2.setCursor(0, 60);
  u8g2.printf("SpO2:%.1f%%", spo2);
  u8g2.sendBuffer();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Uploading to ThingSpeak...");
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey +
                 "&field1=" + String(tempDHT) +
                 "&field2=" + String(humDHT) +
                 "&field3=" + String(tempObj) +
                 "&field4=" + String(tempAmb) +
                 "&field5=" + String(gsrValue) +
                 "&field6=" + String(spo2, 1);
                 


    Serial.println("URL: " + url);
    http.begin(url);
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      Serial.println("ThingSpeak updated");
    } else {
      Serial.printf("HTTP error: %d\n", httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi disconnected!");
  }

  delay(60000);  
}