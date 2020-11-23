#include <wiringPi.h>
class EncoderR
{
private:
    static int const pinA = 2;
    static int const pinB = 3;
    extern static int position;
    extern static unsigned char state;

public:
    static void begin();
    static void update();
    static int read();
};