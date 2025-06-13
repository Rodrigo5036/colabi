```cpp
#include "ColabiOTA.h"

const int LED_BUILTIN = 2; // El pin del LED azul integrado en la ESP32.

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Configura el pin del LED como salida.
  ColabiOTA::begin();
}

void loop() {
  ColabiOTA::handle();
  
  digitalWrite(LED_BUILTIN, HIGH); // Enciende el LED azul.
  delay(1000);                     // Mantiene el LED encendido por 1 segundo.
  digitalWrite(LED_BUILTIN, LOW);  // Apaga el LED azul.
  delay(1000);                     // Mantiene el LED apagado por 1 segundo.
}
```