#pragma once
class Motor
{
    private:
    const unsigned char dirForwardPin;
    const unsigned char powerPin;

    public:
    Motor(unsigned char dirForwardPinLoc, unsigned char powerPinLoc);
    void setPower(double power);
};
