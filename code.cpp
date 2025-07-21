#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "secrets.h"
#include <time.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// PUT YOURE LOCATION HERE 
#define USER_LAT "33.5731"
#define USER_LON "-7.5898"

void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

String getISSPosition() {
  HTTPClient http;
  http.begin("http://api.open-notify.org/iss-now.json");

  int httpCode = http.GET();
  if (httpCode != 200) return "ISS Pos Fail";

  String payload = http.getString();
  StaticJsonDocument<512> doc;
  deserializeJson(doc, payload);

  String lat = doc["iss_position"]["latitude"].as<String>();
  String lon = doc["iss_position"]["longitude"].as<String>();
  http.end();

  return "Lat:" + lat + "\nLon:" + lon;
}

String getNextPassTime() {
  HTTPClient http;
  String url = "http://api.open-notify.org/iss-pass.json?lat=" + String(USER_LAT) + "&lon=" + String(USER_LON);
  http.begin(url);

  int httpCode = http.GET();
  if (httpCode != 200) return "Pass Fail";

  String payload = http.getString();
  StaticJsonDocument<1024> doc;
  deserializeJson(doc, payload);

  time_t risetime = doc["response"][0]["risetime"];
  struct tm *ptm = gmtime(&risetime);

  char timeStr[16];
  sprintf(timeStr, "%02d:%02d:%02d", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
  http.end();
  return String(timeStr);
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA SCL
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED fail");
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Starting...");
  display.display();

  connectWiFi();
  configTime(0, 0, "pool.ntp.org", "time.nist.gov"); 
}

void loop() {
  String pos = getISSPosition();
  String nextPass = getNextPassTime();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("🛰️ ISS Tracker");
  display.println("");
  display.println(pos);
  display.println("Next pass:");
  display.println(nextPass);
  display.display();

  Serial.println(pos);
  Serial.println("Next pass at: " + nextPass);

  delay(15000); 
}

