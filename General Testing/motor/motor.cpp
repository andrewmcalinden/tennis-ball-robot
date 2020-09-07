#include <wiringPi.h>
#include "motor.h"

Motor::Motor(int dirForwardPinLoc, int powerPinLoc)
    : dirForwardPin{dirForwardPinLoc}, powerPin{powerPinLoc}
{
    wiringPiSetup();
    pinMode(dirForwardPin, OUTPUT);
    pinMode(powerPin, PWM_OUTPUT);
}

void Motor::setPower(double power)
{
    if (power < 0)
    {
        //make motor spin backwards
        digitalWrite(dirForwardPin, LOW);

        //give power to motor adjusted (usually from 0 to 1024), negate as power was initially negative
        double adjustedPower = -1 * power * 1023.0;
        pwmWrite(powerPin, adjustedPower);
    }

    else
    { //power >= 0
        //make motor spin forwards
        digitalWrite(dirForwardPin, HIGH);

        //give power to motor adjusted (usually from 0 to 1024)
        double adjustedPower = power * 1023.0;
        pwmWrite(powerPin, adjustedPower);
    }
}
