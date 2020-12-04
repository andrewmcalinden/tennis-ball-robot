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
    double power = -1;
    while (true)
    {
        getline(cin, c);

        if ((c=="run")){
            motorL.setPower(1);
            motorR.setPower(1);
        }
        if ((c=="stop")){
            motorL.setPower(0);
            motorR.setPower(0);
        }
        if ((c=="reverse")){
            motorL.setPower(-1);
            motorR.setPower(-1);
        }
        
    }
}

