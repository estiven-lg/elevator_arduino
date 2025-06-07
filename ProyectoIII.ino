
#include <Servo.h>
#include <Keypad.h>
#include "OpticalSensor.h"
#include "ElevatorDisplay.h"
#include "Elevator.h"

ElevatorDisplay elevatorDisplay;

OpticalSensor opticalSensorsA[] = {
    OpticalSensor(2),
    OpticalSensor(3),
    OpticalSensor(4),
    OpticalSensor(5)};
int pinServoA = 23;
Servo servoA;
Elevator elevatorA(opticalSensorsA, servoA);

OpticalSensor opticalSensorsB[] = {
    OpticalSensor(6),
    OpticalSensor(7),
    OpticalSensor(8),
    OpticalSensor(9)};
int pinServoB = 22;
Servo servoB;

Elevator elevatorB(opticalSensorsB, servoB);

Elevator *selectBestElevator(int targetFloor)
{
  bool aAvailable = !elevatorA.getLocked();
  bool bAvailable = !elevatorB.getLocked();

  if (!aAvailable && !bAvailable)
    return nullptr;

  if (aAvailable && !bAvailable)
    return &elevatorA;
  if (!aAvailable && bAvailable)
    return &elevatorB;

  // Comparar distancia si ambos están disponibles
  int distanceA = abs(elevatorA.getCurrentFloor() - targetFloor);
  int distanceB = abs(elevatorB.getCurrentFloor() - targetFloor);

  Serial.print("Elevator A distance: ");
  Serial.println(elevatorA.getCurrentFloor() - targetFloor);
  Serial.print("Elevator B distance: ");
  Serial.println(elevatorB.getCurrentFloor() - targetFloor);

  return (distanceA <= distanceB) ? &elevatorA : &elevatorB;
}

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// Pines personalizados (filas y columnas)
byte rowPins[ROWS] = {39, 41, 43, 45}; // Filas (R1, R2, R3, R4)
byte colPins[COLS] = {47, 49, 51, 53}; // Columnas (C1, C2, C3, C4)

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);

  elevatorA.begin(pinServoA, 1);
  elevatorB.begin(pinServoB, 2);

  elevatorDisplay.begin();
  elevatorDisplay.setFloorNumber(0);

  pinMode(24, OUTPUT);
}

void loop()
{
  char key = ' ';

  if (Serial1.available())
  {
    key = Serial1.read();
  }


  char keypadKey = keypad.getKey();
  if (keypadKey)
  {
    key = keypadKey;
  }

  if (key != ' ')
  {

    elevatorA.updateActivity();
    elevatorB.updateActivity();

    Serial.print("Tecla presionada: ");
    Serial.println(key);
    Elevator *elevatorC = selectBestElevator(key - '1');

    if (key == '1')
    {

      elevatorC->setFloorNumber(0, elevatorDisplay);
    }
    else if (key == '2')
    {

      elevatorC->setFloorNumber(1, elevatorDisplay);
    }
    else if (key == '3')
    {

      elevatorC->setFloorNumber(2, elevatorDisplay);
    }
    else if (key == '4')
    {

      elevatorC->setFloorNumber(3, elevatorDisplay);
    }
    else if (key == '5')
    {
      elevatorC->setFloorNumber(4, elevatorDisplay);
    }
    else if (key == '*')
    {
      elevatorA.setLocked(!elevatorA.getLocked(), elevatorDisplay);
      Serial.println("Ascensor bloqueado A");
    }
    else if (key == '#')
    {
      elevatorB.setLocked(!elevatorB.getLocked(), elevatorDisplay);
      Serial.println("Ascensor bloqueado A");
    }
    else
    {
      Serial.println("Tecla no válida");
    }
  }

  elevatorA.checkReturnToHome(elevatorDisplay);
  elevatorB.checkReturnToHome(elevatorDisplay);

  //  delay(1000);
}