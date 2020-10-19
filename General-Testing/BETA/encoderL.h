#include <wiringPi.h>
class EncoderL
{
private:
    static int pinA = 2;
    static int pinB = 3;
    static int position = 0;
    static unsigned char state = 0;

public:
    EncoderL();
    static void update();
    static int read();
};