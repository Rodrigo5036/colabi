#include "ColabiOTA.h"

const int blueLedPin = 2; // Asumiendo que el LED azul está en el pin 2

void setup() 
{   
    ColabiOTA::begin(); 
    pinMode(blueLedPin, OUTPUT); 
} 

void loop()
{   
    ColabiOTA::handle(); 
    digitalWrite(blueLedPin, HIGH); 
    delay(2000); 
    digitalWrite(blueLedPin, LOW); 
    delay(2000); 
}