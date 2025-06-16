#include "ColabiOTA.h" 
#include <Adafruit_SSD1306.h> 
#include <Adafruit_GFX.h> 
#include <Wire.h> 

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 

void setup() 
{   
    ColabiOTA::begin(); 
    display.begin(SSD1306_I2C_ADDRESS, OLED_RESET); 
    display.clearDisplay(); 
    display.setTextSize(1); 
    display.setTextColor(SSD1306_WHITE); 
    display.setCursor(0, 0); 
    display.print("Gracias por ver!"); 
    display.display(); 
} 

void loop() 
{   
    ColabiOTA::handle(); 
}