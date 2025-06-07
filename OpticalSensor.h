#ifndef OPTICAL_SENSOR_H  // Evita incluir múltiples veces el mismo archivo
#define OPTICAL_SENSOR_H

#include <Arduino.h>  // Necesario para usar delay(), etc.

class OpticalSensor {
  public:
    OpticalSensor(int pin);
    void begin();
    bool isDetected();
    void waitInterruption();
    void waitDetection();

  private:
    int _pin;
};

#endif