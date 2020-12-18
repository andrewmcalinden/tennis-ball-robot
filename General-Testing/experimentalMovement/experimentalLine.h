#include "movement.h"
#include "../math/pose.h"
class ExperimentalLine : public Movement
{
    private:
    pose initialPose;
    pose finalPose;
    double initialDistance;
    double initialHeading;

    public:
    ExperimentalLine(double distance, double p, double i, double d, double specificF);

    void updatePower(pose currentPose) override;

    void beginMovement(pose startPose) override;
};