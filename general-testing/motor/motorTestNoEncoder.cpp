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
    Motor motorL(DIRECTION_PIN_FORWARD_LEFT, POWER_PIN_LEFT);
    Motor motorR(DIRECTION_PIN_FORWARD_RIGHT, POWER_PIN_RIGHT);

    string c = "";
    while (true)
    {
        getline(cin, c);
        double power = stod(c);
        motorL.setPower(power);
        motorR.setPower(-power);
    }
}

