```cpp
#include "ColabiOTA.h" 
#include <WiFi.h> 
#include <PubSubClient.h> 
#include <DHT.h> 

#define DHTPIN 4     
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE); 
const char* ssid = "tu_SSID"; 
const char* password = "tu_PASSWORD"; 
const char* mqttServer = "tu_MQTT_BROKER"; 
const int mqttPort = 1883; 
const char* topic = "temperatura_humedad"; 

WiFiClient espClient; 
PubSubClient client(espClient); 

void setup() 
{ 
    Serial.begin(115200); 
    WiFi.begin(ssid, password); 
    while (WiFi.status() != WL_CONNECTED) { 
        delay(1000); 
        Serial.println("Conectando a WiFi..."); 
    } 
    Serial.println("Conectado a WiFi"); 
    client.setServer(mqttServer, mqttPort); 
    dht.begin(); 
    ColabiOTA::begin(); 
} 

void loop() 
{ 
    ColabiOTA::handle(); 

    if (!client.connected()) { 
        while (!client.connected()) { 
            Serial.println("Conectando a MQTT..."); 
            if (client.connect("ESP32Client")) { 
                Serial.println("Conectado a MQTT"); 
            } else { 
                Serial.print("Falló con estado: "); 
                Serial.println(client.state()); 
                delay(2000); 
            } 
        } 
    } 
    client.loop(); 

    float h = dht.readHumidity(); 
    float t = dht.readTemperature(); 

    if (isnan(h) || isnan(t)) { 
        Serial.println("Error al leer el DHT!"); 
        return; 
    } 

    String payload = String("Temp: ") + t + " Hum: " + h; 
    client.publish(topic, payload.c_str()); 
    delay(2000); 
}
```