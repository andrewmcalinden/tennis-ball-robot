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
    void update(void);
    int read();
    static void updateCallback(void *this_pointer);
};