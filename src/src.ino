#include "ColabiOTA.h"

const int ledPin = 2; // Pin del LED azul

void setup() {
  pinMode(ledPin, OUTPUT);
  ColabiOTA::begin();
}

void loop() {
  ColabiOTA::handle();
  
  digitalWrite(ledPin, HIGH); // Enciende el LED
  delay(1000);                 // Espera 1 segundo
  digitalWrite(ledPin, LOW);  // Apaga el LED
  delay(1000);                 // Espera 1 segundo
}