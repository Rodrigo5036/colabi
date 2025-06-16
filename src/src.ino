#include "ColabiOTA.h"
#include <ServoESP32.h>

ServoESP32 miServo;

unsigned long previousMillis = 0;
const long intervalo = 1000; // Cambiar este valor a 3000 o 5000 para mover cada 3 o 5 segundos
int angulo = 0;
const int servoPin = 18; // Define servoPin antes de usarlo

void setup() {
  ColabiOTA::begin();
  miServo.attach(servoPin);
  miServo.write(angulo);
}

void loop() {
  ColabiOTA::handle();
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= intervalo) {
    previousMillis = currentMillis;
    angulo = (angulo == 0) ? 90 : 0; // Alternar entre 0 y 90 grados
    miServo.write(angulo);
  }
}