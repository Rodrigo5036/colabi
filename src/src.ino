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
    myServo.write(90); // Mueve el servomotor a 90 grados
    delay(1000); 
    myServo.write(0);  // Mueve el servomotor a 0 grados
    delay(1000); 
}