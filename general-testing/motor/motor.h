#pragma once

#include <wiringPi.h>

class Motor
{
    private:
    const unsigned char dirForwardPin;
    const unsigned char powerPin;

    public:
    Motor(unsigned char dirForwardPinLoc, unsigned char powerPinLoc);
    void setPower(double power);
    ~Motor();
};
