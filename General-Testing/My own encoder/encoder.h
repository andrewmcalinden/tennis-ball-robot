#include <wiringPi.h>
class Encoder
{
private:
    int pinA;
    int pinB;
    int position;
    unsigned char state;
    Encoder& operator=(const Encoder &enc);
    class EncoderHouse
    {
        public:
            static void updateCallback(void);
            static Encoder encoderResident;
    };

public:
    Encoder(int pinALoc, int pinBLoc);
    void update();
    int read();
    //static void updateCallback(void);
};