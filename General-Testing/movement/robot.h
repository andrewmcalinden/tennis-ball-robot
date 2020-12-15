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

        void goStraight(double inches, double kp, double ki, double kd, double f);
        void turnHeading(double finalAngle, double kp, double ki, double kd, double f); //in degrees, turns to that heading (field centric)

        void setMotorPowers(double lPower, double rPower);
};