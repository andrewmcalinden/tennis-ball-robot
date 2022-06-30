class EncoderBad
{
    private:
    int pinA;
    int pinB;
    int position;
    unsigned char state;

    public:
    EncoderBad(int pinALoc, int pinBLoc);
    
    void update();
    int read();

    static void callbackMethod();
    void registerCallback();
};