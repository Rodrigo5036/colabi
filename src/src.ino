```cpp
#include "ColabiOTA.h"

const int ledPin = 2; // Pin del LED interno

void setup() {
  pinMode(ledPin, OUTPUT);
  ColabiOTA::begin();
}

void loop() {
  ColabiOTA::handle();
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}
```