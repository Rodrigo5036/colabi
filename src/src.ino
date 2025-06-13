#include "ColabiOTA.h"

#define LED_BUILTIN 2

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // Apagar el LED azul al inicio
  ColabiOTA::begin();
}

void loop() {
  ColabiOTA::handle();
  digitalWrite(LED_BUILTIN, LOW); // Encender el LED azul
  delay(1000); // Mantenerlo encendido por un segundo
  digitalWrite(LED_BUILTIN, HIGH); // Apagar el LED azul
  delay(1000); // Mantenerlo apagado por un segundo
}