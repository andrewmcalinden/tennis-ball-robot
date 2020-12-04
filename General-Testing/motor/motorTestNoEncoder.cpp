#include "motor.h"
#include <iostream>
#include <wiringPi.h>
#include<unistd.h>

#define DIRECTION_PIN_FORWARD_LEFT 22
#define POWER_PIN_LEFT 23
#define DIRECTION_PIN_FORWARD_RIGHT 27
#define POWER_PIN_RIGHT 26

int main()
{
    wiringPiSetup();

    Motor motorL(DIRECTION_PIN_FORWARD_LEFT, POWER_PIN_LEFT);
    Motor motorR(DIRECTION_PIN_FORWARD_RIGHT, POWER_PIN_RIGHT);
    double Lpower = 1;
    double Rpower = 0;
    while (true)
    {
        while (Rpower < 1){
        motorL.setPower(Lpower);
        motorR.setPower(Rpower);
        Rpower += .01;
        Lpower -= .01;
        usleep(10000);
        }
        while (Rpower > -1){
        motorL.setPower(Lpower);
        motorR.setPower(Rpower);
        Rpower -= .01;
        Lpower += .01;
        usleep(10000);
    }
}
}
