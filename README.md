![app code](https://github.com/user-attachments/assets/ec9ce177-d1fc-49fe-bd9b-e28aa08883b5)# 📋 ESP32-Based Multi-Sensor Health Monitoring System

This project is a real-time embedded health monitoring system built on the ESP32 platform. It reads and displays vital physiological parameters using multiple biomedical sensors and uploads them to the cloud using ThingSpeak for remote monitoring and displaying real time values in a custom created App using MIT App Inventor.

## 🚀 Features

- 🌡️ Measures Body and Ambient Temperature using MLX90614
- 🌬️ Captures Air Temperature & Humidity using DHT22
- 👐 Skin Hydration using GSR Sensor
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

---

## 🛠️ Circuit Connections

| Sensor      | ESP32 Pin |
|-------------|-----------|
| DHT22 Data  | GPIO 4    |
| GSR         | GPIO 34 (ADC) |
| MLX90614 (I2C) | SDA: GPIO 21, SCL: GPIO 22 |
| MAX30102 (I2C) | SDA: GPIO 21, SCL: GPIO 22 |
| OLED (SPI)  | SCL: GPIO 18 , SDA: GPIO 23, RES: GPIO 14, DC: GPIO 27 |

### 📌 DHT22 Pin Mapping
<img src="https://github.com/user-attachments/assets/dc8031b4-6a63-473f-a81d-144438190e59" alt="DHT22 pinout" width="400" height="303" />

---

### 📌 GSR Pinout Mapping
<img src="https://github.com/user-attachments/assets/a132a073-cdfc-493f-966c-a7333d149199" alt="GSR Pinout" width="487" height="419" />

---



### 📌 MAX30102 Pinout Mapping
<img width="486" height="441" alt="MAX30102 pinout" src="https://github.com/user-attachments/assets/14b24f08-3333-4211-bbe5-3f4aad191a03" />

---

### 📌 MLX90614 Pinout Mapping
<img width="491" height="429" alt="MLX90614 pinout" src="https://github.com/user-attachments/assets/5b85b8c5-86e8-40dd-afb4-a66f0de6d8c0" />

---


### 📌 OLED Pinout Mapping
<img width="398" height="312" alt="OLED Display pinout" src="https://github.com/user-attachments/assets/f93fbc59-c639-4118-bdf1-60fbdcc7f2b4" />

---


### 📌 Circuit Diagram
<img src="https://github.com/user-attachments/assets/3af008cf-f184-4421-b15f-aeae49087e11" alt="Circuit Diagram" width="899" height="635" />










📝 Note: Commercial OLED displays typically have 4 pins. However, for SPI communication in this project, we used a 6-pin OLED display. Refer to the pin mapping diagram for details.

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
| 7       | Heart Rate        |

---

## 📁 Folder Structure

```
📆 ESP32-Health-Monitoring
├── src/
│   └── MAX30102,DHT22,OLED,GSR,MLX90614,All Sensors # Main firmware code
├── test_logs/
│   └── breathing_data.csv
│   └── drift test 24h.csv
│   └── screenshots/ Sensor plots, serial monitor screenshots
├── demo/
│   └── demo video.mp4 Short demo video (< 3 min)

├── README.md # This file
```

---

---

## 🌐 Cloud Integration

- ThingSpeak Channel ID: `CHANNEL ID`
- API Key: `API KEY`
- Update interval: Every 60 seconds

Make sure your Wi-Fi credentials and API key are correctly entered.

---

## 📸 Display Preview

Displays the following on OLED (SH1106):
```
T:32.5°C H:47.5%
Obj:31.56°C Amb:28.61°C
GSR:687Ω
SpO2:97.8%
```
---

## 📌 App Interface


![app](https://github.com/user-attachments/assets/a52aac88-f2c7-494e-8277-1fec9ffcf798)
![app code](https://github.com/user-attachments/assets/ea03014e-86ba-4122-8105-0c4888959e59)



## 📌 Notes

- GSR readings: Lower values = higher hydration.
- SpO₂ algorithm uses AC/DC ratio from IR & Red channels.
- SH1106 SPI driver is used via U8g2.
- Ensure proper finger placement on MAX30102 for accurate HR/SpO₂.


## 🧾 Conclusion
This project successfully integrates multiple biomedical and environmental sensors—MLX90614 (temperature), MAX30102 (heart rate and SpO₂), DHT22 (humidity and temperature), and a GSR sensor—with an ESP32 microcontroller and an SH1106 OLED display to create a compact, real-time health and wellness monitoring system. The device not only captures and displays vital physiological parameters locally but also uploads them to the ThingSpeak cloud for remote monitoring and long-term trend analysis.

By combining sensor fusion, wireless data transmission, and edge display, this prototype demonstrates how embedded IoT systems can support real-time health diagnostics. The modular design and open-source architecture make it highly customizable for future applications, including remote patient care, fitness tracking, and stress detection.

This project stands as a foundation for scalable, low-cost, IoT-enabled biomedical monitoring solutions and offers great potential for academic research, healthcare innovation, and embedded system learning.


## 📌 Acknowledgement
I would like to express my heartfelt gratitude to the ELCIA Committee, the International Institute of Information Technology Bangalore (IIITB), and Mr. Kunal Ghosh for granting us the invaluable opportunity to participate in this hackathon.

Their unwavering support and guidance have played a pivotal role in shaping our project. Their dedication to nurturing innovation and creativity is truly inspiring. We are sincerely grateful for the platform they have provided, which has enabled us to explore new ideas, refine our skills, and contribute to a meaningful initiative.

Thank you for this remarkable opportunity.

---

## 👨‍💻 Contributors

- Mahesh V — Hardware, Code Integration, OLED Design
- [Add your team members here]
