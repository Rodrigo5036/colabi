#include "ColabiOTA.h"
#include <Servo.h>

Servo myServo;

void setup() {
  ColabiOTA::begin();
  myServo.attach(9); // Pin donde está conectado el servo
  myServo.write(0);  // Posición inicial
}

void loop() {
  ColabiOTA::handle();
  static unsigned long lastTime = 0;
  if (millis() - lastTime >= 1000) {
    static int angle = 0;
    angle = (angle + 90) % 360;
    myServo.write(angle);
    lastTime = millis();
  }
}