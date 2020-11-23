#include "motor.h"

#define DIRECTION_PIN_FORWARD 2
#define POWER_PIN 10 //GPIO 13
#define BUTTON_IN 6 //GPIO 25

int main()
{
    wiringPiSetup();
    pinMode(BUTTON_IN, INPUT);

    Motor m(DIRECTION_PIN_FORWARD, POWER_PIN);
    double power = 0;
    while (true)
    {
        if (digitalRead(BUTTON_IN) == 0)
        {
            power += 0.01;
            delay(15);
        }
        if (power > 1)
        {
            power = 0;
        }
        //std::cout << power << "\n";
        m.setPower(power);
    }
}
