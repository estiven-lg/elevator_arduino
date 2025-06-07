#ifndef ELEVATOR_DISPLAY_H
#define ELEVATOR_DISPLAY_H

#include <Arduino.h>

class ElevatorDisplay {
  public:
    ElevatorDisplay();
    void begin();
    void setFloorNumber(int floor);
    void setFloorElevator(String floor, int elevator);
    void writeInTheEnd(bool b);
  private:
};

#endif