#include "../motor/motor.h"
#include "../encoder/encoder.h"
class Robot
{
    private:
    Motor l;
    Motor r;

    Encoder encoderL;
    Encoder encoderR;

    public:
        Robot(int lMotorDirPin, int lMotorPowerPin, int rMotorDirPin, int rMotorPowerPin,
              double initialX, double initialY, double initialTheta,
              int lEncoderPin1, int lEncoderPin2, int rEncoderPin1, int rEncoderPin2);

        void goStraight(double inches, double p, double i, double d, double f);
        void turnHeading(double angle); //in degrees

        void setMotorPowers(double lPower, double rPower);
};