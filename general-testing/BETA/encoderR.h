class EncoderR
{
private:
    static unsigned char const pinA = 2;
    static unsigned char const pinB = 3;
    static int position;
    static unsigned char state;

public:
    static void begin();
    static void update();
    static int read();
};