# 📋 ESP32-Based Multi-Sensor Health Monitoring System

This project is a real-time embedded health monitoring system built on the ESP32 platform. It reads and displays vital physiological parameters using multiple biomedical sensors and uploads them to the cloud using ThingSpeak for remote monitoring.

## 🚀 Features

- 🌡️ Measures Body and Ambient Temperature using MLX90614
- 🌬️ Captures Air Temperature & Humidity using DHT22
- 👐 Skin Hydration & Stress Detection using GSR Sensor
- ❤️ Measures Heart Rate and SpO₂ using MAX30102
- 📊 Displays all data on SH1106 OLED via SPI
- ☁️ Uploads sensor data to ThingSpeak (Wi-Fi enabled)

---

## 🧰 Hardware Components

| Component          | Description                              |
|-------------------|------------------------------------------|
| ESP32 Devkit v1   | Main microcontroller                     |
| MLX90614          | IR Thermometer for Object & Ambient Temp |
| DHT22             | Digital Humidity & Temperature Sensor    |
| MAX30102          | Heart Rate and SpO₂ sensor               |
| GSR Sensor        | Measures skin resistance (hydration)     |
| OLED Display (SH1106) | 128x64 display via SPI               |
| Power Supply      | USB / Battery (5V recommended)           |

---

## 🛠️ Circuit Connections

| Sensor      | ESP32 Pin |
|-------------|-----------|
| DHT22 Data  | GPIO 4    |
| GSR         | GPIO 34 (ADC) |
| MLX90614 (I2C) | SDA: GPIO 21, SCL: GPIO 22 |
| MAX30102 (I2C) | SDA: GPIO 21, SCL: GPIO 22 |
| OLED (SPI)  | CLK: GPIO 5, MOSI: GPIO 27, CS: GPIO 14, DC & RST: Defined internally |

---

## 📊 Data Fields (ThingSpeak)

| Field # | Data Type         |
|--------:|-------------------|
| 1       | DHT22 Temperature |
| 2       | DHT22 Humidity    |
| 3       | MLX Object Temp   |
| 4       | MLX Ambient Temp  |
| 5       | GSR Resistance    |
| 6       | SpO₂ %            |

---

## 📁 Folder Structure

```
📆 ESP32-Health-Monitoring
├── src/
│   └── main.cpp                # Main firmware code
├── include/
│   └── (optional header files)
├── lib/
│   └── (optional custom libraries)
├── platformio.ini              # PlatformIO config file
├── README.md                   # This file
```

---

## 🧪 PlatformIO Setup

Make sure you have PlatformIO installed in VSCode.

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/ESP32-Health-Monitoring.git
   cd ESP32-Health-Monitoring
   ```

2. Build & Upload:
   Click the "Upload" button in PlatformIO or run:

   ```bash
   pio run --target upload
   ```

3. Monitor Serial:
   ```bash
   pio device monitor
   ```

---

## ⚙️ platformio.ini

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino

monitor_speed = 115200
upload_speed = 921600

lib_deps = 
  adafruit/Adafruit MLX90614 Library
  adafruit/DHT sensor library
  sparkfun/MAX3010x Pulse and Proximity Sensor Library
  olikraus/U8g2
  adafruit/Adafruit Unified Sensor
  paulstoffregen/Heart Rate

build_flags = 
  -DCORE_DEBUG_LEVEL=3
  -DBUFFER_SIZE=50

upload_port = COM11
```

> Change `COM11` to your actual port.

---

## 🌐 Cloud Integration

- ThingSpeak Channel ID: `3005954`
- API Key: `BZEUAVYF44LJIMNR`
- Update interval: Every 60 seconds

Make sure your Wi-Fi credentials and API key are correctly entered in `main.cpp`.

---

## 📸 Display Preview

Displays the following on OLED (SH1106):
```
T:xx.x H:xx.x
Obj:xx.x Amb:xx.x
GSR:xxxx
SpO2:xx.x%
```

---

## 📌 Notes

- GSR readings: Lower values = higher hydration.
- SpO₂ algorithm uses AC/DC ratio from IR & Red channels.
- SH1106 SPI driver is used via U8g2.
- Ensure proper finger placement on MAX30102 for accurate HR/SpO₂.

---

## 👨‍💻 Contributors

- Mahesh V — Hardware, Code Integration, OLED Design
- [Add your team members here]
