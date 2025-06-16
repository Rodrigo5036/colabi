//1
#include "ColabiOTA.h"
#include <Servo.h>

Servo miServo;

void setup() {
  ColabiOTA::begin();
  miServo.attach(9);  // Pin donde está conectado el servo
}

void loop() {
  ColabiOTA::handle();
  
  for (int angulo = 0; angulo <= 180; angulo += 1) {
    miServo.write(angulo);
    delay(15);
  }
  
  for (int angulo = 180; angulo >= 0; angulo -= 1) {
    miServo.write(angulo);
    delay(15);
  }
}
