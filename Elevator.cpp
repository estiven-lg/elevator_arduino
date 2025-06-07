#include "Elevator.h"
#include "ElevatorDisplay.h"
#include "OpticalSensor.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

Elevator::Elevator(OpticalSensor *opticalSensors, Servo servo)

{
    _opticalSensors = opticalSensors;
    _servo = servo;
}

void Elevator::begin(int pinServo, int elevatorID)
{

    _elevatorID = elevatorID;
    _servo.attach(pinServo);
    _servo.write(90);

    for (int i = 0; i < sizeof(_opticalSensors) / sizeof(_opticalSensors[0]); i++)
    {
        _opticalSensors[i].begin();
    }
}

void Elevator::setFloorNumber(int floor, ElevatorDisplay &elevatorDisplay)
{

    bool isUp = floor > _floorNumber;

    elevatorDisplay.setFloorNumber(floor + 1);
    elevatorDisplay.setFloorElevator(String(floor + 1), _elevatorID);
    elevatorDisplay.writeInTheEnd(isUp);

    int sensorIndex;
    if (_floorNumber == floor)
    {
        Serial.println("El ascensor ya está en el piso solicitado.");
        return;
    }

    if (isUp)
    {
        sensorIndex = floor - 1;
        Serial.println("Subiendo al piso " + String(floor + 1));
        _servo.write(_uploadSpeed);
        _opticalSensors[sensorIndex].waitInterruption();
        Serial.println("casi Llegaste al piso " + String(floor + 1));
        _servo.write(_downloadSpeed);
        _opticalSensors[sensorIndex].waitDetection();
        _servo.write(90);
        Serial.println("Llegaste al piso " + String(floor + 1));

        _floorNumber = floor;
    }
    else
    {
        sensorIndex = floor;
        Serial.println("Bajando al piso " + String(floor + 1));
        _servo.write(_downloadSpeed);
        _opticalSensors[sensorIndex].waitInterruption();
        _servo.write(90);
        Serial.println("Llegaste al piso " + String(floor + 1));

        _floorNumber = floor;
    }

    digitalWrite(24, HIGH);
    delay(500);
    digitalWrite(24, LOW);
}

void Elevator::setLocked(bool lock, ElevatorDisplay &elevatorDisplay)
{
    _locked = lock;

    elevatorDisplay.setFloorElevator(lock ? "lock" : String(_floorNumber), _elevatorID);
}

int Elevator::getLocked()
{
    return _locked;
}

int Elevator::getID()
{
    return _elevatorID;
}

int Elevator::getCurrentFloor()
{
    return _floorNumber;
}

void Elevator::updateActivity()
{
    lastActivityTime = millis();
    returningHome = false;
}

void Elevator::checkReturnToHome( ElevatorDisplay &elevatorDisplay)
{
    if (getCurrentFloor() == 0 || getLocked())
    {
        return;
    }

    if (millis() - lastActivityTime > returnDelay && !returningHome)
    {
        returningHome = true;
        setFloorNumber(0, elevatorDisplay);
        Serial.println("Ascensor retornando al piso 1 por inactividad");
    }
}