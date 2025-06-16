#include "ColabiOTA.h"
#include <Servo.h>

Servo myServo;

void setup() {
  ColabiOTA::begin();
  myServo.attach(9); // Conectar el servo al pin digital 9
}

void loop() {
  ColabiOTA::handle();
  
  for (int pos = 0; pos <= 180; pos += 1) { // Mover el servo de 0 a 180 grados
    myServo.write(pos);
    delay(15);
  }
  for (int pos = 180; pos >= 0; pos -= 1) { // Mover el servo de 180 a 0 grados
    myServo.write(pos);
    delay(15);
  }
}