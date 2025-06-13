```cpp
#include "ColabiOTA.h"

#define LED_BUILTIN 2

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  ColabiOTA::begin();
  digitalWrite(LED_BUILTIN, HIGH); // Encender el LED azul
}

void loop() {
  ColabiOTA::handle();
}
```