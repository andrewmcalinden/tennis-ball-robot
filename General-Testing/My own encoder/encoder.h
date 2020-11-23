class Encoder
{
    private:
    int pinA;
    int pinB;
    int position;
    unsigned char state;

    static Encoder* Encoder::callbackObject;

    public:
    Encoder(int pinALoc, int pinBLoc);
    void update();
    int read();

    static void Encoder::callbackMethod();
    void Encoder::registerCallback();
};