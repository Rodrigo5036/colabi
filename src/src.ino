#include "ColabiOTA.h"
#include <ESP32Servo.h>

Servo miServo;

unsigned long previousMillis = 0;
const long intervalo = 1000; // cambiar a 3000 o 5000 si quieres más lento
int angulo = 0;
const int servoPin = 18;

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
    angulo = (angulo == 0) ? 90 : 0;
    miServo.write(angulo);
  }
}
