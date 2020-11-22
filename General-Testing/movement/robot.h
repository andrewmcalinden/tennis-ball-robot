#include "../BETA/encoderL.h"
#include "../BETA/encoderR.h"
#include "motorPowers.h"
class Robot
{
    private:
    Motor l;
    Motor r;

    double lPower;
    double rPower;

    typedef std::function<MotorPowers()> MotorPowersFunc;
    typedef std::vector<MotorPowersFunc> FuncVector;

    FuncVector movements;

    //Encoders are static

    public:
    Robot(int lMotorDirPin, int lMotorPowerPin, int rMotorDirPin, int rMotorPowerPin, double initialX, double initialY, double initialTheta);

    void goStraight(double inches, double p, double i, double d, double f);
    void turnHeading(double angle); //in degrees

    void setMotorPowers(double lPower, double rPower);
    void update();
}