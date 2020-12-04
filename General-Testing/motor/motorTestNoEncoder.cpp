#include "motor.h"
#include <iostream>
#include <wiringPi.h>
#include<unistd.h>

#define DIRECTION_PIN_FORWARD_LEFT 22
#define POWER_PIN_LEFT 23
#define DIRECTION_PIN_FORWARD_RIGHT 16
#define POWER_PIN_RIGHT 26

int main()
{
    wiringPiSetup();

    Motor motorL(DIRECTION_PIN_FORWARD_LEFT, POWER_PIN_LEFT);
    Motor motorR(DIRECTION_PIN_FORWARD_RIGHT, POWER_PIN_RIGHT);
    double power = 0;
    while (true)
    {
        while (power < 1){
        motorL.setPower(power);
        motorR.setPower(power);
        power += .01;
        usleep(50000);
        }
        while (power > -1){
        motorL.setPower(power);
        motorR.setPower(power);
        power -= .01;
        usleep(50000);
    }
}
}
