class Motor
{
private:
    unsigned char dirForwardPin;
    unsigned char powerPin;

public:
    Motor(unsigned char dirForwardPinLoc, unsigned char powerPinLoc);
    void setPower(double power);
};
