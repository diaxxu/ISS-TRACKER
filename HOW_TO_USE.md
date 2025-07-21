#  How to Use: ESP32 ISS Tracker with OLED

Track the International Space Station in real-time and see when it’ll fly over your location (Casablanca by default) using an ESP32 and OLED display.

---

##  What You Need

- ESP32 dev board
- SSD1306 OLED (128x64 I2C)
- Internet (WiFi)
- PlatformIO (or Arduino IDE, )

---

##  Wiring (ESP32 to OLED)

| OLED Pin | ESP32 Pin |
|----------|-----------|
| VCC      | 3.3V      |
| GND      | GND       |
| SDA      | GPIO 21   |
| SCL      | GPIO 22   |

---

##  Setup Steps

1. **Clone the repo**
   ```bash
   git clone https://github.com/your-username/iss-tracker-esp32
