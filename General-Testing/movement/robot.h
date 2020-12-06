#include "../motor/motor.h"
#include "../encoder/encoder.h"
#include <vector>
class Robot
{
    private:
    Motor l;
    Motor r;

    Encoder encoderL;
    Encoder encoderR;

    enum Movement
    {
        straight,
        turn
    };
    std::vector<Movement> movements;

    unsigned char numMovements;
    unsigned char currentIndex;

    Vector startPos;
    Vector finalPos;

    double power;

    public:
    Robot(int lMotorDirPin, int lMotorPowerPin, int rMotorDirPin, int rMotorPowerPin,
            double initialX, double initialY, double initialTheta,
            int lEncoderPin1, int lEncoderPin2, int rEncoderPin1, int rEncoderPin2);

    void goStraight(double inches, double p, double i, double d, double f);
    void turnHeading(double angle); //in degrees

    void setMotorPowers(double lPower, double rPower);

    void goStraightPowerCalculations(Vector initialPos, Vector currentPos, Vector finalPos, double power);

    void run();
};