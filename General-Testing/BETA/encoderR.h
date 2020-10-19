#include <wiringPi.h>
class EncoderR
{
private:
    static int const pinA = 0;
    static int const pinB = 7;
    static int position;
    static unsigned char state;

public:
    static void begin();
    static void update();
    static int read();
};