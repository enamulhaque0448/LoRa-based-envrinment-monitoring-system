# 🌡️ LoRa Environment Monitoring System

**Byte Us Team Project**  
*Real-time environmental monitoring using ESP32, LoRa SX1278, and a web dashboard*

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![ESP32](https://img.shields.io/badge/ESP32-Compatible-green)](https://www.espressif.com/)
[![LoRa](https://img.shields.io/badge/LoRa-SX1278-blue)](https://www.semtech.com/lora)
[![PHP](https://img.shields.io/badge/Backend-PHP/MySQL-purple)](https://www.php.net/)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)

## 📋 Table of Contents
- [Project Overview](#-project-overview)
- [Key Features](#-key-features)
- [System Architecture](#-system-architecture)
- [Hardware Requirements](#-hardware-requirements)
- [Software Requirements](#-software-requirements)
- [Installation Guide](#-installation-guide)
- [File Structure](#-file-structure)
- [Configuration](#-configuration)
- [Usage](#-usage)
- [Dashboard Features](#-dashboard-features)
- [Troubleshooting](#-troubleshooting)
- [Team Members](#-team-members)
- [License](#-license)

## 🎯 Project Overview

This project implements a complete IoT-based environmental monitoring system that collects real-time temperature, humidity, and pressure data using ESP32 microcontrollers with LoRa communication. The system transmits sensor readings wirelessly over long distances, stores them in a MySQL database, and visualizes the data on a responsive web dashboard with interactive charts.

**Project Type:** University Course Project  
**Course:** MP & I 
**Duration:** 4 Weeks  
**Team:** Byte Us

## ✨ Key Features

- **Real-time Monitoring**: Live environmental data collection and transmission
- **Long-Range Communication**: LoRa technology for up to 2km range
- **Multi-Sensor Integration**: DHT11 (temperature/humidity) + BMP280 (pressure)
- **Web Dashboard**: Interactive visualization with Chart.js
- **Database Storage**: MySQL for historical data retention
- **Responsive Design**: Mobile-friendly interface
- **Automatic Updates**: Real-time data refresh every 2 seconds
- **Historical Analysis**: View up to 50 previous readings

## 🏗️ System Architecture

```
┌─────────────────────────────────────────────────────────────────────────┐
│                         SYSTEM ARCHITECTURE                              │
└─────────────────────────────────────────────────────────────────────────┘

┌─────────────┐     ┌─────────────┐     ┌─────────────┐     ┌─────────────┐
│   SENSOR    │     │   ESP32     │     │   ESP32     │     │   WEB       │
│   MODULE    │────▶│   WITH      │────▶│   LORA      │────▶│   SERVER    │
│ (DHT11 +    │ I2C/│   LORA      │ LoRa│   RECEIVER  │HTTP │ (XAMPP)     │
│  BMP280)    │ GPIO│   SENDER    │433MHz             │     │             │
└─────────────┘     └─────────────┘     └─────────────┘     └─────────────┘
                                                                    │
                                                                    ▼
                                                            ┌─────────────┐
                                                            │   WEB       │
                                                            │   DASHBOARD │
                                                            │   (HTML/JS) │
                                                            └─────────────┘
                                                                    │
                                                                    ▼
                                                            ┌─────────────┐
                                                            │   MYSQL     │
                                                            │   DATABASE  │
                                                            └─────────────┘
```

## 🛠️ Hardware Requirements

### Components List

| Component | Quantity | Specification | Purpose |
|-----------|----------|---------------|---------|
| ESP32 Development Board | 2 | ESP32-WROOM-32 | Microcontroller |
| LoRa Module (SX1278) | 2 | 433MHz | Long-range communication |
| DHT11 Sensor | 1 | Digital Temperature & Humidity | Environmental sensing |
| BMP280 Sensor | 1 | I2C Pressure Sensor | Atmospheric pressure |
| LoRa Antenna | 2 | 433MHz Spring Antenna | Signal transmission |
| Breadboard | 2 | 830 points | Circuit assembly |
| Jumper Wires | 20+ | Male-to-Male/Female | Connections |
| USB Cable | 2 | Micro USB | Power & Programming |
| Power Supply | Optional | 5V/2A | Extended operation |

### 📍 Pin Connections

#### **Transmitter (Sensor Node)**
```
ESP32 GPIO      ->   Component
──────────────────────────────────
GPIO 4          ->   DHT11 Data
GPIO 21 (SDA)   ->   BMP280 SDA
GPIO 22 (SCL)   ->   BMP280 SCL
GPIO 5 (SS)     ->   LoRa NSS
GPIO 14         ->   LoRa RST
GPIO 2          ->   LoRa DIO0
3.3V            ->   All VCC pins
GND             ->   All GND pins
```

#### **Receiver (Gateway)**
```
ESP32 GPIO      ->   Component
──────────────────────────────────
GPIO 5 (SS)     ->   LoRa NSS
GPIO 14         ->   LoRa RST
GPIO 2          ->   LoRa DIO0
GPIO 16 (RX2)   ->   Optional Serial
GPIO 17 (TX2)   ->   Optional Serial
3.3V            ->   LoRa VCC
GND             ->   LoRa GND
```

## 💻 Software Requirements

### Development Tools
- **Arduino IDE** (v2.0 or later) - [Download](https://www.arduino.cc/en/software)
- **XAMPP** (v8.0 or later) - [Download](https://www.apachefriends.org/)
- **Modern Web Browser** (Chrome, Firefox, Edge)
- **Serial Terminal** (Arduino Serial Monitor, Putty, or similar)

### Arduino Libraries
Install via Arduino Library Manager:
1. **LoRa** by Sandeep Mistry
2. **Adafruit BMP280 Library**
3. **DHT sensor library** by Adafruit
4. **Adafruit Unified Sensor**

### Database Requirements
- MySQL 5.7 or later
- PHP 7.4 or later
- Apache Web Server

## 📥 Installation Guide

### Step 1: Hardware Assembly

1. **Transmitter Setup:**
   - Connect DHT11 to ESP32 GPIO4
   - Connect BMP280 to ESP32 I2C pins (GPIO21/22)
   - Connect LoRa module as per pin mapping
   - Attach 433MHz antenna to LoRa module

2. **Receiver Setup:**
   - Connect LoRa module to second ESP32
   - Ensure antenna is properly connected
   - Connect ESP32 to computer via USB

### Step 2: Database Setup

1. **Start XAMPP:**
   ```bash
   # Start Apache and MySQL services
   ```

2. **Create Database:**
   ```sql
   -- Run in phpMyAdmin or MySQL console
   CREATE DATABASE env_monitor_db;
   USE env_monitor_db;
   
   CREATE TABLE readings (
       id INT AUTO_INCREMENT PRIMARY KEY,
       temperature FLOAT NOT NULL,
       humidity FLOAT NOT NULL,
       pressure FLOAT NOT NULL,
       reg_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
   );
   ```

3. **Database Configuration:**
   Edit `db_connect.php` with your credentials:
   ```php
   <?php
   $servername = "localhost";
   $username = "root";      // Change if different
   $password = "";          // Set your MySQL password
   $dbname = "env_monitor_db";
   ?>
   ```

### Step 3: Upload Code to ESP32

1. **Transmitter (lora_sender.ino):**
   - Open Arduino IDE
   - Select ESP32 board (Tools → Board → ESP32 Dev Module)
   - Set correct COM port
   - Upload `lora_sender.ino` to transmitter ESP32

2. **Receiver (ESP32 with LoRa receiver code):**
   - Upload receiver code (not included, needs separate receiver script)
   - Ensure receiver is connected to computer for data forwarding

### Step 4: Web Dashboard Setup

1. **Place Files in XAMPP htdocs:**
   ```
   C:/xampp/htdocs/lora-monitor/
   ├── index.html
   ├── get_data.php
   ├── save_data.php
   ├── db_connect.php
   └── lora_receiver.php (if using HTTP receiver)
   ```

2. **Configure Receiver Endpoint:**
   - Update `save_data.php` to match your receiver's IP/endpoint
   - Ensure CORS headers are properly set if needed

3. **Access Dashboard:**
   Open browser and navigate to:
   ```
   http://localhost/lora-monitor/
   ```

## 📁 File Structure

```
LORA-ENVIRONMENT-MONITOR/
├── ARDUINO_CODE/
│   ├── lora_sender.ino          # ESP32 transmitter code
│   └── lora_receiver.ino        # ESP32 receiver code (to be added)
│
├── WEB_DASHBOARD/
│   ├── index.html               # Main dashboard interface
│   ├── db_connect.php           # Database connection
│   ├── save_data.php            # API to save incoming data
│   ├── get_data.php             # API to fetch historical data
│   └── assets/
│       ├── css/
│       │   └── style.css        # Additional styles (optional)
│       └── js/
│           └── custom.js        # Additional JavaScript (optional)
│
├── DATABASE/
│   └── env_monitor_db.sql       # Database schema
│
├── DOCUMENTATION/
│   ├── circuit_diagram.png      # Wiring diagram
│   ├── pinout.png               # Pin configuration
│   └── screenshots/             # Dashboard screenshots
│
└── README.md                    # This file
```

## ⚙️ Configuration

### LoRa Parameters
Modify in `lora_sender.ino`:
```cpp
// LoRa frequency (adjust based on your region)
#define LORA_FREQUENCY 433E6  // 433 MHz for EU/Asia

// Spreading factor (range vs data rate trade-off)
LoRa.setSpreadingFactor(7);    // Range: 6-12, higher = longer range

// Signal bandwidth
LoRa.setSignalBandwidth(125E3); // 125 kHz (standard)

// Coding rate
LoRa.setCodingRate4(5);        // Error correction: 5-8
```

### Transmission Interval
Change in `loop()` function:
```cpp
delay(5000);  // 5 seconds between transmissions
// delay(10000);  // 10 seconds for battery saving
```

### Web Dashboard Settings
Modify in JavaScript section of `index.html`:
```javascript
// Data refresh interval (milliseconds)
setInterval(fetchData, 2000);  // Update every 2 seconds

// Number of historical points to display
const historyPoints = 50;  // Last 50 readings
```

## 🚀 Usage

### Starting the System

1. **Power Up Hardware:**
   - Connect transmitter to power source
   - Connect receiver to computer/USB power
   - Ensure antennas are vertical for best range

2. **Monitor Serial Output:**
   ```
   Transmitter Serial Output:
   Starting LoRa Sender...
   LoRa Initializing OK!
   Sending packet: 25.5,65.2,1013.2
   
   Receiver Serial Output (if implemented):
   Received packet: 25.5,65.2,1013.2
   RSSI: -45, SNR: 12.5
   ```

3. **Access Dashboard:**
   - Open `http://localhost/lora-monitor/`
   - Data should appear within 10 seconds

### Testing the System

1. **Sensor Verification:**
   - Breathe on DHT11 sensor → Humidity should increase
   - Warm sensor with fingers → Temperature should increase
   - Change altitude → Pressure should change

2. **Range Testing:**
   - Start with devices close together
   - Gradually increase distance
   - Monitor RSSI values (higher negative = weaker signal)

3. **Database Verification:**
   Check phpMyAdmin to confirm data is being stored:
   ```sql
   SELECT * FROM readings ORDER BY id DESC LIMIT 5;
   ```

## 📊 Dashboard Features

### Real-time Display
- **Temperature Card**: Red gradient with thermometer icon
- **Humidity Card**: Green gradient with cloud icon  
- **Pressure Card**: Blue gradient with gauge icon

### Interactive Charts
1. **Historical Trends Chart:**
   - Line graph showing last 50 readings
   - Toggle visibility of each parameter
   - Smooth bezier curves for visualization

2. **Latest Readings Bar Chart:**
   - Comparison of current sensor values
   - Color-coded bars for quick assessment
   - Auto-scaling Y-axis

### Additional Features
- **Auto-refresh**: Updates every 2 seconds
- **Responsive Design**: Works on mobile and desktop
- **Timestamp Display**: Shows last update time
- **Team Information**: Footer with contributor names

## 🔧 Troubleshooting

### Common Issues & Solutions

| Issue | Possible Cause | Solution |
|-------|---------------|----------|
| No data on dashboard | Database not connected | Check `db_connect.php` credentials |
| LoRa not initializing | Wrong pins or frequency | Verify pin connections in code |
| Sensors not reading | Wiring issues or power | Check 3.3V and GND connections |
| Dashboard not loading | File path incorrect | Ensure files are in htdocs folder |
| Data not updating | JavaScript errors | Check browser console (F12) |
| Poor LoRa range | Antenna orientation | Keep antennas vertical and unobstructed |

### Serial Debug Messages
Enable debug output by adding to `setup()`:
```cpp
Serial.begin(115200);
while (!Serial);  // Wait for serial connection
Serial.println("Debug mode enabled");
```

### Testing Individual Components
1. **Test DHT11 Alone:**
   ```cpp
   #include "DHT.h"
   DHT dht(4, DHT11);
   void setup() { Serial.begin(115200); dht.begin(); }
   void loop() { 
     Serial.print("Temp: "); Serial.println(dht.readTemperature());
     delay(2000); 
   }
   ```

2. **Test LoRa Alone:**
   ```cpp
   #include <LoRa.h>
   void setup() {
     LoRa.begin(433E6);
     LoRa.beginPacket();
     LoRa.print("TEST");
     LoRa.endPacket();
   }
   ```

## 👥 Team Members

**Byte Us Team** - MP&I Course Project

| Name | Role | Contribution |
|------|------|--------------|
| **Tahsid** | Project Lead | System architecture & integration |
| **Akib** | Hardware Specialist | Circuit design & sensor integration |
| **Armaan** | Software Developer | ESP32 programming & LoRa configuration |
| **Aryan** | Web Developer | Dashboard design & backend API |
| **Enamul** | Database Engineer | MySQL setup & data management |

### Project Timeline
- **Week 1**: Research & component selection
- **Week 2**: Hardware assembly & testing
- **Week 3**: Software development & integration
- **Week 4**: Dashboard development & final testing

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

```
MIT License

Copyright (c) 2024 Byte Us Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
```

## 🔗 Useful Resources

- [ESP32 Official Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [LoRa SX1278 Datasheet](https://www.semtech.com/uploads/documents/DS_SX1276-7-8-9_W_APP_V5.pdf)
- [Arduino LoRa Library](https://github.com/sandeepmistry/arduino-LoRa)
- [Chart.js Documentation](https://www.chartjs.org/docs/latest/)
- [XAMPP Documentation](https://www.apachefriends.org/docs/)

## 🙏 Acknowledgments

- **Course Instructor**: For guidance and support
- **University**: For providing laboratory facilities
- **Open Source Community**: For libraries and tools
- **Semtech**: For LoRa technology documentation

---

**⭐ If you find this project useful, please consider giving it a star on GitHub!**

*Last Updated: December 2024*  
*Project Status: Completed*  
*Course: IoT and Embedded Systems*

---

**Note for Future Development:**
- Consider adding MQTT protocol for better scalability
- Implement data export functionality (CSV/PDF)
- Add alert/notification system for threshold values
- Include battery level monitoring for remote nodes
- Develop mobile app companion
