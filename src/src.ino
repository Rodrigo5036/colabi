#include "ColabiOTA.h"
#include <ESP32Servo.h>

Servo myServo;

void setup() {
  ColabiOTA::begin();
  myServo.attach(18); // Conectar al pin 18
  myServo.write(90);  // Posición inicial 90 grados
}

void loop() {
  ColabiOTA::handle();
  myServo.write(0);   // Mover a 0 grados
  delay(1000);
  myServo.write(180); // Mover a 180 grados
  delay(1000);
}