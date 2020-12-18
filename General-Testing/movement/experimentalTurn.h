#include "movement.h"
#include "../math/pose.h"
class ExperimentalTurn : public Movement
{
    private:
    double initialHeading;
    double finalHeading;
    double initialAngleDiff;

    public:
    ExperimentalTurn(double endHeading, double p, double i, double d, double specificF);

    void updatePower(pose currentPose);

    void beginMovement(pose startPose);
};