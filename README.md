#  ISS Tracker with ESP32 + OLED

A small project to track the International Space Station using an ESP32 and OLED display.

##  What it does
- Connects to WiFi
- Calls ISS API to get current position
- Displays ISS location on OLED
- Checks when ISS will fly above your location (FUNCTIONNAL RN)

##  What you need
- ESP32
- SSD1306 OLED (I2C)
- Open Notify API (no key needed)
- Internet access

##  Libraries used
- WiFi.h
- HTTPClient.h
- ArduinoJson.h
- Adafruit_SSD1306
- time.h
- Adafruit_GFX.h

##  How to use
1. Clone this repo
2. Put your WiFi credentials in `secrets.h`
3. Upload using PlatformIO or Arduino IDE
4. enter
5. success

##  API docs
- Current location: http://api.open-notify.org/iss-now.json
- Flyover times: http://api.open-notify.org/iss-pass.json



