#include "ColabiOTA.h"
#include <Servo.h>

Servo myServo;
const int servoPin = 18; // Cambia el pin según tu conexión

void setup() {
   Serial.begin(115200); // Añadir inicialización del puerto serie para depuración
   ColabiOTA::begin();
   myServo.attach(servoPin);
   myServo.write(0); // Inicializa el servo en la posición 0
}

void loop() {
   ColabiOTA::handle();
   for (int pos = 0; pos <= 180; pos += 1) {
       myServo.write(pos);
       delay(15);
   }
   for (int pos = 180; pos >= 0; pos -= 1) {
       myServo.write(pos);
       delay(15);
   }
}