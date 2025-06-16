#include "ColabiOTA.h"
#include <Servo.h>

Servo myServo;

void setup() {
    ColabiOTA::begin();
    myServo.attach(9); // Asigna el pin 9 al servo
}

void loop() {
    ColabiOTA::handle();
    // Control del servo
    for (int pos = 0; pos <= 180; pos += 1) {
        myServo.write(pos);
        delay(15);
    }
    for (int pos = 180; pos >= 0; pos -= 1) {
        myServo.write(pos);
        delay(15);
    }
}