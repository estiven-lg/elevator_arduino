#include "OpticalSensor.h"
#include <Arduino.h>

OpticalSensor::OpticalSensor(int pin) {
  _pin = pin;
}

void OpticalSensor::begin() {
  pinMode(_pin, INPUT_PULLUP);
}

bool OpticalSensor::isDetected() {
  return digitalRead(_pin) == HIGH;
}

void OpticalSensor::waitInterruption() {
  bool oldState = false;
  while (isDetected() || !oldState) {
    oldState = isDetected();
    // Serial.println("Esperando interrupción...");
    // Serial.println("Estado actual: " + String(isDetected()));
    // Serial.println("Estado anterior: " + String(oldState));
    delay(50);
  }
}

void OpticalSensor::waitDetection() {

  while (!isDetected()) {

    delay(50);
  }
}