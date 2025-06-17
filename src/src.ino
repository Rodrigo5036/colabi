#include "ColabiOTA.h"
#include <Adafruit_NeoPixel.h>

#define LED_PIN 2 // Pin del LED interno del ESP32
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  ColabiOTA::begin();
  pixels.begin();
}

void loop() {
  ColabiOTA::handle();
  pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // RGB: Rojo
  pixels.show();
  delay(1000);
  pixels.setPixelColor(0, pixels.Color(0, 255, 0)); // RGB: Verde
  pixels.show();
  delay(1000);
  pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // RGB: Azul
  pixels.show();
  delay(1000);
}