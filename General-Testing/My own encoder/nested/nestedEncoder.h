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
    void makeObjectStatic();

    class EncoderReference
    {
    public:
        NestedEncoder *callbackObject; //works if not static
        //void setCallBackObject();
    };
};