#include "../BETA/encoderL.h"
#include "../BETA/encoderR.h"
#include "motorPowers.h"
class Robot
{
    private:
    Motor l;
    Motor r;

    std::clock_t timer;

    //Encoders are static, put member variables here if needed

    public:
    Robot(int lMotorDirPin, int lMotorPowerPin, int rMotorDirPin, int rMotorPowerPin, double initialX, double initialY, double initialTheta);

    void goStraight(double inches, double p, double i, double d, double f);
    void turnHeading(double angle); //in degrees
    void run();
}