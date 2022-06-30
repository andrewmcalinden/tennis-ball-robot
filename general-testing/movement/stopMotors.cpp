#define DIRECTION_PIN_FORWARD_LEFT 22
#define POWER_PIN_LEFT 23
#define DIRECTION_PIN_FORWARD_RIGHT 27
#define POWER_PIN_RIGHT 26
#define COLLECTOR_PIN 4

#include <iostream>
#include "../motor/motor.h"
#include <wiringPi.h>

int main()
{
    Motor motorL(DIRECTION_PIN_FORWARD_LEFT, POWER_PIN_LEFT);
    Motor motorR(DIRECTION_PIN_FORWARD_RIGHT, POWER_PIN_RIGHT);
    pinMode(COLLECTOR_PIN, OUTPUT);

    motorL.setPower(0);
    motorR.setPower(0);
    digitalWrite(COLLECTOR_PIN, LOW);
}