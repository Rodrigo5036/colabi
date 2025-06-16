#include "ColabiOTA.h"
#include <ESP32Servo.h>

Servo servo;

void setup() 
{   
    ColabiOTA::begin(); 
    servo.attach(13);
    servo.write(45);
    delay(1000);
    servo.write(90);
    delay(2000);
    servo.write(180);
    delay(1000); // Agregado para permitir que el servo alcance la posición 180
}

void loop()
{   
    ColabiOTA::handle(); 
}