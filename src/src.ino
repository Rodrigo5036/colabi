#include "ColabiOTA.h"

const int ledPin = 2;
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

void setup() {
  ColabiOTA::begin();
  pinMode(ledPin, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}

void loop() {
  ColabiOTA::handle();
  
  // 1. Blink the LED every second
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
  
  // 2. Send temperature data (mock data)
  float temperature = 25.5; // Replace with actual temperature reading
  Serial.print("Temperature: ");
  Serial.println(temperature);
  
  // 3. Check for OTA updates
  ColabiOTA::handle();
}