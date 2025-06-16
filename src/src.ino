```cpp
#include "ColabiOTA.h"

const int ledPin = 12;

void setup() {
  ColabiOTA::begin();
  pinMode(ledPin, OUTPUT);
}

void loop() {
  ColabiOTA::handle();
  digitalWrite(ledPin, HIGH); // Enciende el LED
  delay(1000);                // Espera 1 segundo
  digitalWrite(ledPin, LOW);  // Apaga el LED
  delay(1000);                // Espera 1 segundo
}
```