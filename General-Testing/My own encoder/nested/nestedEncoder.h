class NestedEncoder
{
private:
    int pinA;
    int pinB;
    int position;
    unsigned char state;

public:
    NestedEncoder(int pinALoc, int pinBLoc);
    void update();
    int read();

    static void callbackMethod();
    void registerCallback();

    class EncoderReference
    {
    public:
        static NestedEncoder *callbackObject;
        //void setCallBackObject();
    };
};