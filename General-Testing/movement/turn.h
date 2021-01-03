#include "../motor/motorPowers.h"
#include <ctime>
class Turn
{
    private:
    double finalHeading;
    double initialAngleDiff;

    double leftPower;
    double rightPower;

    double kp;
    double ki;
    double kd;
    double f;

    std::clock_t timer;
    double pastTime;
    double currentTime;

    double error;
    double pastError;

    double integral;

    bool done;

    public:
    Turn(double endHeading, double p, double i, double d, double specificF);

    motorPowers getPowers();
    void updatePower(double heading);

    void beginMovement(double startHeading);

    bool finished();
};