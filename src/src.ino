```cpp
#include <WiFi.h>
#include <OneSpeed32.h>
#include "ColabiOTA.h"

#define WIFI_SSID "your-ssid"
#define WIFI_PASSWORD "your-password"

OneSpeed32 motor;

void setup() {
    // Configurar el inicio OTA
    ColabiOTA::begin();

    // Configurar WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }

    // Inicializar motor OneSpeed32
    motor.begin();
    
    // Configurar velocidad del motor
    motor.setSpeed(120); // Ajusta la velocidad a 120 RPM
}

void loop() {
    // Manejar OTA
    ColabiOTA::handle();

    // Tu lógica adicional si es necesario
    motor.update(); // Actualizar el motor en cada iteración del loop
}
```