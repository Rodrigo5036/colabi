#include "ColabiOTA.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* mqtt_server = "your_MQTT_Broker";

void setup() {
    Serial.begin(115200);
    ColabiOTA::begin();
    
    dht.begin();
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    client.setServer(mqtt_server, 1883);
}

void loop() {
    ColabiOTA::handle();

    if (!client.connected()) {
        // Reconnect to MQTT
        while (!client.connected()) {
            Serial.print("Attempting MQTT connection...");
            if (client.connect("ESP32_Client")) {
                Serial.println("connected");
            } else {
                Serial.print("failed, rc=");
                Serial.print(client.state());
                delay(2000);
            }
        }
    }

    client.loop();
    
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    if (!isnan(h) && !isnan(t)) {
        String payload = String("Humidity: ") + h + " Temperature: " + t;
        client.publish("home/temperature", payload.c_str());
    }
    delay(2000);
}