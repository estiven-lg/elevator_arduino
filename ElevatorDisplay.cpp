#include "ElevatorDisplay.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define YELLOW_HEIGHT 16
#define BLUE_HEIGHT (SCREEN_HEIGHT - YELLOW_HEIGHT)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

ElevatorDisplay::ElevatorDisplay()
{
    // Constructor vacío
}

void ElevatorDisplay::begin()
{
    // Wire.begin(sda, scl);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("Error en pantalla OLED");
        while (1)
            ;
    }
    display.clearDisplay();
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.drawLine(0, YELLOW_HEIGHT - 1, SCREEN_WIDTH - 1, YELLOW_HEIGHT - 1, WHITE);
    display.display();
}

void ElevatorDisplay::setFloorNumber(int floor)
{
    display.startWrite();
    display.setTextColor(WHITE);
    display.setTextSize(1.25);
    display.setCursor(0, 0);

    display.fillRect(0, 0, display.width(), 8, BLACK);
    display.display();

    display.setCursor(0, 0);
    display.println("Piso Actual:" + String(floor));
    display.endWrite();
    display.display();
}

void ElevatorDisplay::setFloorElevator(String floor, int elevator)
{
    display.setTextSize(2);
    display.setTextColor(WHITE);

    if (elevator == 1)
    {
        display.fillRect(0, YELLOW_HEIGHT + 5, display.width(), 16, BLACK);
        display.setCursor(0, YELLOW_HEIGHT + 5);
        display.println("A1:" + floor);
    }

    if (elevator == 2)
    {
        display.fillRect(0, YELLOW_HEIGHT + 25, display.width(), 16, BLACK);
        display.setCursor(0, YELLOW_HEIGHT + 25);
        display.println("A2:" + floor);
    }

    display.display();
}

void ElevatorDisplay::writeInTheEnd(bool b)
{
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, SCREEN_HEIGHT - 8);
    display.fillRect(0, SCREEN_HEIGHT - 8, display.width(), 8, BLACK);
    display.println(b ? "bajando" : "subiendo");
    display.display();
}
