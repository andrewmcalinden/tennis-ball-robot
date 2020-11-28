class Encoder
{
    public:
    int pinA;
    int pinB;
    int position;
    unsigned char state;

    Encoder(int pinALoc, int pinBLoc);
    
    int read();

    void registerCallback();
};