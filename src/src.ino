#include "ColabiOTA.h" 
#include <WiFi.h> 
#include <Adafruit_Sensor.h> 
#include <DHT.h> 
#include <Adafruit_SSD1306.h> 

#define DHTPIN 4 
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE); 
Adafruit_SSD1306 display(128, 64, &Wire, -1); 

void setup() 
{ 
    Serial.begin(115200); 
    ColabiOTA::begin(); 
    WiFi.begin("SSID", "PASSWORD"); 
    while (WiFi.status() != WL_CONNECTED) { 
        delay(1000); 
        Serial.println("Conectando a WiFi..."); 
    } 
    dht.begin(); 
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
    display.clearDisplay(); 
    display.setTextSize(1); 
    display.setTextColor(SSD1306_WHITE); 
    display.setCursor(0, 0); 
    display.print("Conectado a WiFi!"); 
    display.display(); 
    delay(2000); 
} 

void loop() 
{ 
    ColabiOTA::handle(); 
    float h = dht.readHumidity(); 
    float t = dht.readTemperature(); 

    if (isnan(h) || isnan(t)) { 
        Serial.println("Error al leer el sensor DHT!"); 
        return; 
    } 

    display.clearDisplay(); 
    display.setCursor(0, 0); 
    display.print("Humedad: "); 
    display.print(h); 
    display.print(" %"); 
    display.print("Temperatura: "); 
    display.print(t); 
    display.print(" *C"); 
    display.display(); 
    delay(2000); 
}