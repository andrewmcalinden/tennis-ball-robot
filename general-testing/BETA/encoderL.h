class EncoderL
{
private:
    static unsigned char const pinA = 0;
    static unsigned char const pinB = 7;
    static int position;
    static unsigned char state;

public:
    static void begin();
    static void update();
    static int read();
};