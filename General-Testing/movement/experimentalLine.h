#include "movement.h"
#include "../math/pose.h"
class ExperimentalLine : public Movement
{
    private:
    pose finalPose;
    double initialDistance;
    double initialHeading;

    public:
    ExperimentalLine(pose endPose, double p, double i, double d, double specificF);

    void updatePower(pose currentPose);

    void beginMovement(pose startPose);
};