class ExperimentalEncoder
{
private:
    int pinA;
    int pinB;
    int position;
    unsigned char state;
    int location;

public:
    ExperimentalEncoder(int pinALoc, int pinBLoc);
    int read();

    static void callbackMethod();
    void registerCallback();

};