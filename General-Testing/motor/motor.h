class Motor
{
private:
    int dirForwardPin;
    int powerPin;

public:
    Motor(int dirForwardPinLoc, int powerPinLoc);
    void setPower(double power);
};
