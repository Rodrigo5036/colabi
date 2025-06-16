#include "ColabiOTA.h"
#include <Servo.h>

Servo myServo;

void setup() {
  ColabiOTA::begin();
  myServo.attach(13);
  myServo.write(30);
  delay(1000);
  myServo.write(50);
  delay(1000);
  myServo.write(90);
}

void loop() {
  ColabiOTA::handle();
}