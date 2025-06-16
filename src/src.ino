#include "ColabiOTA.h" 
#include <Wire.h>
#include <Adafruit_SSD1306.h> 
#include <Adafruit_GFX.h> 

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 

void setup() { 
  ColabiOTA::begin(); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.clearDisplay(); 
  display.setTextSize(2); 
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(0, 0); 
  display.print("Hola Mundo!"); 
  display.display(); 
} 

void loop() { 
  ColabiOTA::handle(); 
}