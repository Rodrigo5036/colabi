#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "ColabiOTA.h"

const char* ssid = "tuSSID";
const char* password = "tuContrasena";

AsyncWebServer server(80);

void setup() {
    ColabiOTA::begin();
    
    // Conectar a la red WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }
    
    // Configurar el servidor para servir subtítulos
    server.on("/subtitulos", HTTP_GET, [](AsyncWebServerRequest *request){
        StaticJsonDocument<200> doc;
        doc["subtitulos"] = "Subtítulos realizados por la comunidad de Amara.org";
        
        String output;
        serializeJson(doc, output);
        request->send(200, "application/json", output);
    });
    
    // Iniciar el servidor
    server.begin();
}

void loop() {
    ColabiOTA::handle();
}