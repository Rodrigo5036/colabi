#include "ColabiOTA.h"
#include <ESP32Servo.h>

Servo myServo;

void setup() {
  ColabiOTA::begin();
  myServo.attach(18); // Pin donde está conectado el servo
}

void loop() {
  ColabiOTA::handle();
  
  myServo.write(45);
  delay(1000);
  myServo.write(90);
  delay(1000);
  myServo.write(180);
  delay(1000);
}