#include <Arduino.h>
#include <ESP32Servo.h>

class Wheel
{
    int tensionPin;
    Servo wheelTension;
    int forwardPin;
    int backwardPin;

public:
    Wheel() {}

    Wheel(int tensionPin, int forwardPin, int backwardPin)
        : tensionPin(tensionPin), forwardPin(forwardPin), backwardPin(backwardPin)
    {
        pinMode(forwardPin, OUTPUT);
        pinMode(backwardPin, OUTPUT);

        wheelTension.attach(tensionPin);
    }

    void write(float speed)
    {
        speed *= 1024;

        digitalWrite(tensionPin, abs(speed) > 0);
        digitalWrite(forwardPin, speed > 0);
        digitalWrite(backwardPin, speed < 0);
    }
};