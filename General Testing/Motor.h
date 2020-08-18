#include <wiringPi.h>
class Motor
{

    private:
        int dirForwardPin;
        int dirBackwardPin;
        int powerPin;

    public:
        Motor(int dirForwardPinLoc, int dirBackwardPinLoc, int powerPinLoc);
        
        void setPower(double power);
};
