class EncoderR
{
private:
    static int const pinA = 2;
    static int const pinB = 3;
    static int position;
    static unsigned char state;

public:
    static void begin();
    static void update();
    static int read();
};