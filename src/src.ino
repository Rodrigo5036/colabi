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
    myServo.write(45);
    delay(2000);
    myServo.write(90);
    delay(2000);
    myServo.write(180);
    delay(2000);
    ColabiOTA::handle(); 
} 