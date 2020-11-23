#include "motor.h"
#include <iostream>
#define DIRECTION_PIN_FORWARD 2
#define POWER_PIN 10 //GPIO 13

int main()
{
    wiringPiSetup();
    Motor m(DIRECTION_PIN_FORWARD, POWER_PIN);
    double power = 0;
    while (true)
    {
        power += 0.01;
        delay(15);
        if (power > 1)
        {
            power = 0;
        }
        std::cout << power << "\n";
        m.setPower(power);
    }
}
