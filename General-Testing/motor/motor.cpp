#include "motor.h"
#include <cmath>
#include <wiringPi.h>
Motor::Motor(unsigned char dirForwardPinLoc, unsigned char powerPinLoc)
    : dirForwardPin{dirForwardPinLoc}, powerPin{powerPinLoc}
{
    wiringPiSetup();
    pinMode(dirForwardPin, OUTPUT);
    pinMode(powerPin, PWM_OUTPUT);
    pwmSetClock(1500); //~7khz
    pwmSetRange(100);
}

void Motor::setPower(double power)
{
    if (fabs(power) > 1) return;

    power /= 2.0;
    if (power < 0) //if power less than -0.5, dont do anything
    {
        //make motor spin backwards
        digitalWrite(dirForwardPin, LOW);

        //give power to motor adjusted (usually from 0 to 99), negate as power was initially negative
        double adjustedPower = -1 * power * 99;
        pwmWrite(powerPin, adjustedPower);
    }

    else //power >= 0 but <= .5
    {   //make motor spin forwards
        digitalWrite(dirForwardPin, HIGH);

        //give power to motor adjusted (usually from 0 to 99)
        double adjustedPower = power * 99;
        pwmWrite(powerPin, adjustedPower);
    }
}
