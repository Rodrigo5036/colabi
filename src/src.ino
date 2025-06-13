#include "ColabiOTA.h"

const int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  ColabiOTA::begin();
}

void loop() {
  ColabiOTA::handle();
  digitalWrite(ledPin, HIGH);   // Encender el LED
  delay(1000);                   // Mantenerlo encendido por 1 segundo
  digitalWrite(ledPin, LOW);    // Apagar el LED
  delay(1000);                   // Mantenerlo apagado por 1 segundo
}