#include <wiringPi.h>
class Encoder
{
private:
    int pinA;
    int pinB;
    int position;
    unsigned char state;

public:
    Encoder(int pinALoc, int pinBLoc);
    void update();
    int read();
    static void updateCallback(void);
};