#include "ColabiOTA.h"
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_BME280 bme;

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* mqtt_server = "YOUR_MQTT_BROKER";

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32Client")) {
      client.subscribe("home/sensors");
    } else {
      delay(5000);
    }
  }
}

void setup() {
  ColabiOTA::begin();
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  client.setServer(mqtt_server, 1883);
  
  if (!bme.begin(0x76)) {
    while (1);
  }
  
  display.begin(SSD1306_I2C_ADDRESS, OLED_RESET);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  ColabiOTA::handle();
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");
  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");
  display.display();

  String payload = "Temperature: " + String(temperature) + " C, Humidity: " + String(humidity) + " %";
  client.publish("home/sensors", payload.c_str());

  delay(5000);
}