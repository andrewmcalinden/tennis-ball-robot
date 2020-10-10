#include "motor.h"
#include <iostream>

#define DIRECTION_PIN_FORWARD 2
#define POWER_PIN 23 //GPIO 13
#define JOYSTICK 6 //GPIO 25

int main()
{
    wiringPiSetup();

    Motor m(DIRECTION_PIN_FORWARD, POWER_PIN);
    while (true)
    {
        m.setPower(1);
    }
}
