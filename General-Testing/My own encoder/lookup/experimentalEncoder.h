class ExperimentalEncoder
{
public:
    int pinA;
    int pinB;
    int position;
    unsigned char state;

    ExperimentalEncoder(int pinALoc, int pinBLoc);
    int read();

    void registerCallback();
};