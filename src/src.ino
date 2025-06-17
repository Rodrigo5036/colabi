```cpp
#include <ESP32Servo.h>
#include "ColabiOTA.h"

Servo myServo;
int servoPin = 18;

void setup() {
  ColabiOTA::begin();
  myServo.attach(servoPin);
  myServo.write(0);  // Inicia el servomotor en la posición 0 grados
}

void loop() {
  ColabiOTA::handle();

  for (int pos = 0; pos <= 180; pos += 1) {  // Mueve el servomotor desde 0 a 180 grados
    myServo.write(pos);
    delay(15);  // Espera para que el movimiento sea visible
  }

  for (int pos = 180; pos >= 0; pos -= 1) {  // Mueve el servomotor de regreso desde 180 a 0 grados
    myServo.write(pos);
    delay(15);  // Espera para que el movimiento sea visible
  }
}
```