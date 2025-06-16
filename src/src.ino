#include "ColabiOTA.h"
#include <Servo.h>

Servo myServo;
int pos = 0;
bool increasing = true;

void setup() {
  ColabiOTA::begin();
  myServo.attach(13);
  myServo.write(pos);
}

void loop() {
  ColabiOTA::handle();
  
  if (increasing) {
    pos++;
    if (pos >= 180) {
      increasing = false;
    }
  } else {
    pos--;
    if (pos <= 0) {
      increasing = true;
    }
  }
  
  myServo.write(pos);
  delay(1000);
}