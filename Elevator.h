#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "ElevatorDisplay.h"

#include <Arduino.h>
#include "OpticalSensor.h"
#include <Servo.h>

class Elevator
{
public:
  Elevator(OpticalSensor *opticalSensors, Servo servo);
  void begin(int pinServo, int elevatorID = 0);
  void setFloorNumber(int floor, ElevatorDisplay &elevatorDisplay);
  void setLocked(bool lock, ElevatorDisplay &elevatorDisplay);
  int getLocked();
  int getID();
  int getCurrentFloor();
  unsigned long lastActivityTime;
  const unsigned long returnDelay = 30000;
  bool returningHome = false;
  void checkReturnToHome(ElevatorDisplay &elevatorDisplay);
  void updateActivity();

private:
  OpticalSensor *
      _opticalSensors;
  Servo _servo;
  int _floorNumber = 0;
  int _elevatorID = 0;
  int _downloadSpeed = 65;
  int _uploadSpeed = 115;
  bool _locked = false;
};

#endif