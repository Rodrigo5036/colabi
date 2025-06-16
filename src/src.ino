#include "ColabiOTA.h"
#include <WiFi.h> 

void setup() 
{   
    Serial.begin(115200);
    Serial.println("Iniciando el ESP32...");
    WiFi.begin("tu_ssid", "tu_contraseña");
    ColabiOTA::begin(); 
}

void loop() 
{   
    ColabiOTA::handle(); 

    // Ejemplo de conexión a una red WiFi
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Conectando a WiFi...");

        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.println("Esperando conexión...");
        }
        Serial.println("Conectado a la red WiFi");
    }

    // Código adicional aquí para ejecutar tu lógica
}