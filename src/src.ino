#include "ColabiOTA.h"
#include <ESP32Servo.h>

Servo myServo;

void setup() {
  ColabiOTA::begin();
  myServo.attach(13);  // Conecta el servomotor al pin GPIO 13
  myServo.write(90);   // Mueve el servomotor a la posición central
}

void loop() {
  ColabiOTA::handle();

  // Ejemplo de movimiento del servo de 0 a 180 grados y de regreso
  for (int pos = 0; pos <= 180; pos++) {
    myServo.write(pos);
    delay(15);
  }
  for (int pos = 180; pos >= 0; pos--) {
    myServo.write(pos);
    delay(15);
  }
}