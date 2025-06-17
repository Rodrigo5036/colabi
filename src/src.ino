#include "ColabiOTA.h"
#include <ESP32Servo.h>

Servo myServo;

void setup() {
  ColabiOTA::begin();
  myServo.attach(18); // Pin GPIO 18, cambiar según configuración
  myServo.write(90); // Posición inicial del servo a 90 grados
}

void loop() {
  ColabiOTA::handle();
  delay(2000); // Pausa de 2 segundos
  myServo.write(0); // mueve el servo a 0 grados
  delay(2000); // Pausa de 2 segundos
  myServo.write(180); // mueve el servo a 180 grados
}