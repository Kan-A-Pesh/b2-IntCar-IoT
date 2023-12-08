#include <Arduino.h>
#include <modules/Wheel.cpp>

class Car
{
    Wheel frontLeftWheel;
    Wheel frontRightWheel;
    Wheel rearLeftWheel;
    Wheel rearRightWheel;

public:
    Car() {}

    Car(Wheel frontLeft, Wheel frontRight, Wheel rearLeft, Wheel rearRight)
        : frontLeftWheel(frontLeft), frontRightWheel(frontRight),
          rearLeftWheel(rearLeft), rearRightWheel(rearRight) {}

    void drive(float speed)
    {
        turn(0, speed);
    }

    void left(float speed)
    {
        turn(-1, speed);
    }

    void right(float speed)
    {
        turn(1, speed);
    }

    void turn(float angle, float speed)
    {
        float leftSpeed = speed;
        float rightSpeed = speed;

        if (angle < 0)
        {
            leftSpeed = speed * (1 + angle);
        }
        else if (angle > 0)
        {
            rightSpeed = speed * (1 - angle);
        }

        frontLeftWheel.write(leftSpeed);
        frontRightWheel.write(rightSpeed);
        rearLeftWheel.write(leftSpeed);
        rearRightWheel.write(rightSpeed);
    }

    void stop()
    {
        frontLeftWheel.write(0);
        frontRightWheel.write(0);
        rearLeftWheel.write(0);
        rearRightWheel.write(0);
    }

    void manual_frontleft(float speed)
    {
        frontLeftWheel.write(speed);
    }

    void manual_frontright(float speed)
    {
        frontRightWheel.write(speed);
    }

    void manual_rearleft(float speed)
    {
        rearLeftWheel.write(speed);
    }

    void manual_rearright(float speed)
    {
        rearRightWheel.write(speed);
    }
};
