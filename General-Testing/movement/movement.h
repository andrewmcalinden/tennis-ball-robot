#include "../motor/motorPowers.h"
#include <ctime>
class Movement
{
    protected:
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
    motorPowers getPowers();
    bool finished();
};