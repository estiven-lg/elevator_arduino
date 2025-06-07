#ifndef BLINK_MODULE_H  // Evita incluir múltiples veces el mismo archivo
#define BLINK_MODULE_H

#include <Arduino.h>  // Necesario para usar delay(), etc.

class BlinkModule {
  public:
    BlinkModule(int pin);  // Constructor
    void begin();          // Inicializar el pin
    void blink(int delayTime);  // Hacer parpadear el LED

  private:
    int _pin;  // Guarda el pin del LED
};

#endif