#include "ColabiOTA.h"

void setup() {
  ColabiOTA::begin();
  Serial.begin(115200);
  // Configuración de WiFi
  WiFi.begin("TuSSID", "TuContraseña");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a WiFi");
}

void loop() {
  ColabiOTA::handle();
  // Funcionalidad adicional
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 1000) {
    lastPrint = millis();
    Serial.println("El ESP32 está funcionando...");
  }
}