#include "ColabiOTA.h"  
#include <ESP32Servo.h>  

Servo myServo;  
const int servoPin = 18;  
unsigned long previousMillis = 0;  
const long interval = 5000;  

void setup()  
{  
    ColabiOTA::begin();  
    myServo.attach(servoPin);  
    myServo.write(0);  
}  

void loop()  
{  
    ColabiOTA::handle();  
    unsigned long currentMillis = millis();  
    if (currentMillis - previousMillis >= interval)  
    {  
        previousMillis = currentMillis;  
        myServo.write(90);  
        delay(1000);  
        myServo.write(0);  
    }  
}  