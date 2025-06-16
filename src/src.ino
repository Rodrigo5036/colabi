#include "ColabiOTA.h"
#include <Servo.h>

Servo motor;
unsigned long previousMillis = 0;
const long interval1 = 1000; // 1 segundo
const long interval2 = 2000; // 2 segundos
bool moveFast = true;

void setup() {
  ColabiOTA::begin();
  motor.attach(18); // Pin donde está conectado el servo (cambiar a un pin compatible con ESP32)
  motor.write(0); // Posición inicial
}

void loop() {
  ColabiOTA::handle();
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= (moveFast ? interval1 : interval2)) {
    previousMillis = currentMillis;
    motor.write(90); // Mover el motor a 90 grados
    delay(1000); // Esperar un segundo
    motor.write(0); // Regresar el motor a 0 grados
  }
}