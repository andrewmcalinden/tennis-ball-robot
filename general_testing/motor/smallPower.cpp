#include "motor.h"
#include <iostream>
#include <string>
#include <wiringPi.h>
#include<unistd.h>

#define DIRECTION_PIN_FORWARD_LEFT 22
#define POWER_PIN_LEFT 23
#define DIRECTION_PIN_FORWARD_RIGHT 27
#define POWER_PIN_RIGHT 26

using namespace std;


int main()
{
    wiringPiSetup();

    Motor motorL(DIRECTION_PIN_FORWARD_LEFT, POWER_PIN_LEFT);
    Motor motorR(DIRECTION_PIN_FORWARD_RIGHT, POWER_PIN_RIGHT);
        motorL.setPower(.2);
        motorR.setPower(-.2);
    delay(2000);
    motorL.setPower(0);
        motorR.setPower(0);
}

