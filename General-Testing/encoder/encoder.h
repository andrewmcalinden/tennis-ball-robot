class Encoder
{
    public:
    unsigned char pinA;
    unsigned char pinB;
    int position;
    unsigned char state;

    Encoder(int pinALoc, int pinBLoc);

    int read();

    void registerCallback();
};