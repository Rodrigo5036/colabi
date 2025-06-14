//1
#include "ColabiOTA.h"
#include <WiFi.h>

const char* ssid = "TU_SSID";
const char* password = "TU_PASSWORD";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conexión WiFi exitosa!");
  ColabiOTA::begin();
}

void loop() {
  ColabiOTA::handle();
}
