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
    ColabiOTA::handle(); 
    myServo.write(90);
    delay(5000);
    myServo.write(0);
    delay(5000);
}