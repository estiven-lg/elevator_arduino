#include "BlinkModule.h"
#include <Arduino.h>

BlinkModule::BlinkModule(int pin) {
  _pin = pin;
}

void BlinkModule::begin() {
  pinMode(_pin, OUTPUT);
}

void BlinkModule::blink(int tiempo) {
  digitalWrite(_pin, HIGH);
  delay(tiempo);
  digitalWrite(_pin, LOW);
  delay(tiempo);
}
