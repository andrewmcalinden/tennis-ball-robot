#include "motor.h"
#include <iostream>

#define DIRECTION_PIN_FORWARD 2
#define DIRECTION_PIN_BACKWARD 1
#define POWER_PIN 3 //GPIO 22
#define BUTTON_IN 6 //GPIO 25

int main(){
    wiringPiSetup();
    pinMode(BUTTON_IN, INPUT);

    Motor m(DIRECTION_PIN_FORWARD, DIRECTION_PIN_BACKWARD, POWER_PIN);
    double power = 0;
    while (true)
    {
        if (digitalRead(BUTTON_IN) == 0)
        {
            power += 0.01;
        }
        std::cout << power << "\n";
        m.setPower(power);
    }
}
