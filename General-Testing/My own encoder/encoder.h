#include <wiringPi.h>
class Encoder
{
private:
    int pinA;
    int pinB;
    int position;
    double state;

public:
    Encoder(int pinALoc, int pinBLoc);
    void update();
    int read();
};