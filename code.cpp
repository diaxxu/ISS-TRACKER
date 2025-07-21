#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "secrets.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA, SCL

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Booting...");
  display.display();

  connectWiFi();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://api.open-notify.org/iss-now.json");

    int httpCode = http.GET();
    if (httpCode == 200) {
      String payload = http.getString();
      StaticJsonDocument<512> doc;
      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {
        const char* lat = doc["iss_position"]["latitude"];
        const char* lon = doc["iss_position"]["longitude"];

        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("🌍 ISS Tracker");
        display.println("");
        display.print("Lat: ");
        display.println(lat);
        display.print("Lon: ");
        display.println(lon);
        display.display();

        Serial.println("Updated coords:");
        Serial.print("Latitude: "); Serial.println(lat);
        Serial.print("Longitude: "); Serial.println(lon);
      }
    } else {
      Serial.println("HTTP Error");
    }
    http.end();
  } else {
    Serial.println("WiFi lost. Reconnecting...");
    connectWiFi();
  }

  delay(10000); // update every 10 sec
}
