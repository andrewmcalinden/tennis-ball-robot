#include <wiringPi.h>
class Encoder
{
private:
    int pinA;
    int pinB;
    double position;
    double state;

public:
    Encoder(int pinALoc, int pinBLoc);
    void update();
};