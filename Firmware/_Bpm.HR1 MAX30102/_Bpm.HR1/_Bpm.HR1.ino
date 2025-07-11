#include <Wire.h>
#include "MAX30105.h"
#include <U8g2lib.h>

MAX30105 particleSensor;

U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(
  U8G2_R0,
  5,
  27,
  14
);

const int MY_BUFFER_SIZE = 100;
long irBuffer[MY_BUFFER_SIZE];
int bufferIndex = 0;

unsigned long lastBeatTime = 0;
float beatsPerMinute = 0;
float beatAvg = 0;

float avgSpO2 = 0;
int spo2ReadingCount = 0;

unsigned long lastPrintTime = 0;
const unsigned long printInterval = 60000;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_ncenB14_tr);

  if (!particleSensor.begin(Wire)) {
    Serial.println("MAX30102 not found. Check wiring.");
    while (1);
  }

  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x1F);
  particleSensor.setPulseAmplitudeIR(0x1F);
  particleSensor.setPulseAmplitudeGreen(0);

  Serial.println("Place your finger on the sensor.");
}

void loop() {
  long irValue = particleSensor.getIR();
  long redValue = particleSensor.getRed();

  irBuffer[bufferIndex] = irValue;
  bufferIndex = (bufferIndex + 1) % MY_BUFFER_SIZE;

  int prev = (bufferIndex + MY_BUFFER_SIZE - 2) % MY_BUFFER_SIZE;
  int curr = (bufferIndex + MY_BUFFER_SIZE - 1) % MY_BUFFER_SIZE;
  int next = bufferIndex;

  int threshold = 50000;

  if (
    irBuffer[curr] > irBuffer[prev] &&
    irBuffer[curr] > irBuffer[next] &&
    irBuffer[curr] > threshold
  ) {
    unsigned long now = millis();
    unsigned long delta = now - lastBeatTime;

    if (delta > 300 && delta < 1500) {
      beatsPerMinute = 60000.0 / delta;

      static float bpmHistory[4] = {0};
      static int bpmIndex = 0;

      bpmHistory[bpmIndex++] = beatsPerMinute;
      bpmIndex %= 4;

      beatAvg = 0;
      for (int i = 0; i < 4; i++) beatAvg += bpmHistory[i];
      beatAvg /= 4;
    }

    lastBeatTime = millis();
  }

  float ratio = (float)redValue / (irValue + 1);
  float estSpO2 = 110.0 - (25.0 * ratio);
  estSpO2 = constrain(estSpO2, 85, 100);

  avgSpO2 += estSpO2;
  spo2ReadingCount++;

  if (millis() - lastPrintTime >= printInterval) {
    lastPrintTime = millis();

    float finalSpO2 = (spo2ReadingCount > 0) ? avgSpO2 / spo2ReadingCount : 0;

    Serial.print("BPM: ");
    Serial.print(beatAvg, 1);
    Serial.print(" | SpO2: ");
    Serial.println(finalSpO2, 1);

    u8g2.clearBuffer();
    u8g2.setCursor(0, 22);
    u8g2.print("BPM: ");
    u8g2.print(beatAvg, 1);

    u8g2.setCursor(0, 48);
    u8g2.print("SpO2: ");
    u8g2.print(finalSpO2, 1);
    u8g2.print("%");

    u8g2.sendBuffer();

    avgSpO2 = 0;
    spo2ReadingCount = 0;
  }

  delay(10);
}
