#include "ColabiOTA.h"

#define LED_PIN 12

void setup() {
  pinMode(LED_PIN, OUTPUT);
  ColabiOTA::begin();
}

void loop() {
  ColabiOTA::handle();
  
  // Control del LED
  static bool ledState = false;
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
  delay(1000); // Cambia el estado del LED cada segundo
}