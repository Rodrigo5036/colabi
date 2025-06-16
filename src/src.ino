#include "ColabiOTA.h"
#include <Servo.h>

Servo myServo;

void setup() {
  ColabiOTA::begin();
  myServo.attach(18); // Pin del servo
}

void loop() {
  ColabiOTA::handle();
  
  // Ejemplo de movimiento del servo
  for (int pos = 0; pos <= 180; pos += 1) { // va de 0 a 180 grados
    myServo.write(pos);
    delay(15); // espera a que el servo llegue a la posición
  }
  for (int pos = 180; pos >= 0; pos -= 1) { // va de 180 a 0 grados
    myServo.write(pos);
    delay(15);
  }
}