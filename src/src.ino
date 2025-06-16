#include "ColabiOTA.h"
#include <Servo.h>

Servo myServo;

void setup() {
  ColabiOTA::begin();
  myServo.attach(2); // Cambia el número 2 por el pin donde conectas el servo
}

void loop() {
  ColabiOTA::handle();
  
  // Ejemplo de movimiento del servo
  for (int pos = 0; pos <= 180; pos += 1) {
    myServo.write(pos);
    delay(15);
  }
  for (int pos = 180; pos >= 0; pos -= 1) {
    myServo.write(pos);
    delay(15);
  }
}