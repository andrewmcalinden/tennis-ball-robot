#include "../motor/motor.h"
#include <iostream>
#include <string>
#include <wiringPi.h>
#include<unistd.h>

#define DIRECTION_PIN_FORWARD_LEFT 22
#define POWER_PIN_LEFT 23
#define DIRECTION_PIN_FORWARD_RIGHT 27
#define POWER_PIN_RIGHT 26


int main()
{
    Motor motorL(DIRECTION_PIN_FORWARD_LEFT, POWER_PIN_LEFT);
    Motor motorR(DIRECTION_PIN_FORWARD_RIGHT, POWER_PIN_RIGHT);

    motorL.setPower(.065);
    motorR.setPower(-.065);
    delay(5000);
    std::cout << "stopping motors" << std::endl;
    motorL.setPower(0);
    motorR.setPower(0);
}