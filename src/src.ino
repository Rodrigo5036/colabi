#include "ColabiOTA.h"
#include <Adafruit_NeoPixel.h>

#define PIN_NEOPIXEL 5
#define NUM_PIXELS 30

Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
  ColabiOTA::begin();
  pixels.begin();
  pixels.show();
}

void loop() {
  ColabiOTA::handle();
  lightspeedEffect();
}

void lightspeedEffect(); // Declarar la función antes de usarla

void lightspeedEffect() {
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0)); // Verde
    pixels.show();
    delay(30);
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Apagar
  }
  for (int i = NUM_PIXELS - 1; i >= 0; i--) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0)); // Verde
    pixels.show();
    delay(30);
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Apagar
  }
}