#include <wiringPi.h>
class EncoderL
{
private:
    static int pinA;
    static int pinB;
    static int position;
    static unsigned char state;

public:
    EncoderL();
    static void update();
    static int read();
};