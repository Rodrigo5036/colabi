//1234
#include "ColabiOTA.h"

const int ledPin = 2;
unsigned long lastToggle = 0;
bool ledState = false;

void setup() {
  ColabiOTA::begin();
  pinMode(ledPin, OUTPUT);
}

void loop() {
  ColabiOTA::handle();  // Mantiene activo el servidor de configuración

  // Parpadeo del LED cada 500 ms
  if (millis() - lastToggle >= 500) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    lastToggle = millis();
  }
}
