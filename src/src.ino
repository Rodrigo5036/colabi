#include "ColabiOTA.h"
#include <ESP32Servo.h>

Servo myServo;

void setup() 
{  
    ColabiOTA::begin(); 
    myServo.attach(13);
    myServo.write(45);
    delay(1000);
    myServo.write(90);
    delay(2000);
    myServo.write(180);
    delay(1000); // Se añade un delay para que el servo tenga tiempo de llegar a la posición.
}

void loop()
{   
    ColabiOTA::handle(); 
}