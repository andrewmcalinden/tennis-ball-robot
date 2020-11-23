#include "../motor/motor.h"
#include "../BETA/encoderL.h"
#include "../BETA/encoderR.h"
class Robot
{
    private:
    Motor l;
    Motor r;

    //Encoders are static

    public:
    //Robot(int lMotorDirPin, int lMotorPowerPin, int rMotorDirPin, int rMotorPowerPin, double initialX, double initialY, double initialTheta);

    void goStraight(double inches, double p, double i, double d, double f);
    void turnHeading(double angle); //in degrees

    void setMotorPowers(double lPower, double rPower);

    void printEncoders();
};