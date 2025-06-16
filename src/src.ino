#include "ColabiOTA.h"

#define LED_PIN 12

void setup() {
  ColabiOTA::begin();
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  ColabiOTA::handle();
  digitalWrite(LED_PIN, HIGH); // Enciende el LED azul
  delay(1000);                 // Mantiene encendido por 1 segundo
  digitalWrite(LED_PIN, LOW);  // Apaga el LED azul
  delay(1000);                 // Mantiene apagado por 1 segundo
}