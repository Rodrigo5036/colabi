#include "ColabiOTA.h"
#include <ESP32Servo.h>

Servo myServo;

void setup() 
{   
    ColabiOTA::begin(); 
    myServo.attach(13);
}

void loop() 
{   
    myServo.write(90);
    delay(1000);
    myServo.write(45);
    delay(1000);
    myServo.write(100);
    delay(1000);
}