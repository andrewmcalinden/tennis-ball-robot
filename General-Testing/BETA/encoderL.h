#include <wiringPi.h>
class EncoderL
{
private:
    static int const pinA = 0;
    static int const pinB = 7;
    extern static int position;
    extern static unsigned char state;

public:
    static void begin();
    static void update();
    static int read();
};