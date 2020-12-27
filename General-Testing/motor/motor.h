class Motor
{
private:
    unsigned char dirForwardPin;
    unsigned char powerPin;

public:
    Motor(int dirForwardPinLoc, int powerPinLoc);
    void setPower(double power);
};
