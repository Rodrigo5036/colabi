```cpp
#include "ColabiOTA.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

const char* ssid = "tu_SSID";
const char* password = "tu_PASSWORD";
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttTopic = "esp32/dht";

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(115200);
    ColabiOTA::begin();
    dht.begin();
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando a WiFi...");
    }
    Serial.println("Conectado a WiFi");
    client.setServer(mqttServer, mqttPort);
}

void loop() {
    ColabiOTA::handle();
    if (!client.connected()) {
        // Reconnect to MQTT
        while (!client.connected()) {
            Serial.println("Intentando conectar al MQTT...");
            if (client.connect("ESP32Client")) {
                Serial.println("Conectado al MQTT");
            } else {
                Serial.print("Error de conexión, rc=");
                Serial.print(client.state());
                delay(2000);
            }
        }
    }
    client.loop();
    
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
        Serial.println("Error al leer del DHT!");
        return;
    }

    String payload = "Temperatura: " + String(t) + " °C, Humedad: " + String(h) + " %";
    client.publish(mqttTopic, payload.c_str());
    
    delay(60000); // Publicar cada 60 segundos
}
```