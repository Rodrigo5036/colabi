#include "ColabiOTA.h"
#include <ESP32Servo.h>

static const int servoPin = 13;

Servo servo1;

void setup() {
  ColabiOTA::begin();
  servo1.attach(servoPin);
}

void loop() {
  ColabiOTA::handle();
  
  for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
    servo1.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }

  for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
    servo1.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }
}
