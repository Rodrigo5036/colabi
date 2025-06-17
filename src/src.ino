#include <ESP32Servo.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 15
#define SERVO_PIN 2

Servo myservo;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);

#include "ColabiOTA.h"

void setup() {
  ColabiOTA::begin();
  
  myservo.attach(SERVO_PIN);
  strip.begin();
  strip.show();
  
  myservo.write(0);  // Inicializa el servo en la posición 0 grados
  strip.setPixelColor(0, strip.Color(0, 0, 0));  // Apaga el LED
  strip.show();
}

void loop() {
  ColabiOTA::handle();
  
  for (int pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos);
    strip.setPixelColor(0, strip.Color(0, 255, 0));  // Enciende el LED en verde
    strip.show();
    delay(15);
  }

  for (int pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    strip.setPixelColor(0, strip.Color(255, 0, 0));  // Cambia el LED a rojo
    strip.show();
    delay(15);
  }
}