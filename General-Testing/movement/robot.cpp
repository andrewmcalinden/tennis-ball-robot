#include "robot.h"

Robot::Robot(int lMotorDirPin, int lMotorPowerPin, int rMotorDirPin, int rMotorPowerPin, double initialX, double initialY, double initialTheta)
    : l{MotorDirPin, lMotorPowerPin}, r{rMotorDirPin, rMotorPowerPin} //initialize motors
{
    setPose(initialX, initialY, initialTheta);
}

void Robot::goStraight(double inches, double p, double i, double d, double f)
{
    double kp = p;
    double ki = i;
    double kd = d;

    timer = std::clock();

    double pastTime = 0;
    double currentTime = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);

    double initialX = getX();
    double initialY = gety();

    double startHypo = hypot(initialX, initalY);
    double finalHypo = startHypo + inches;
    
    double ratio = finalHypo / startHypo;
    double finalX = ratio * initialX;
    double finalY = ratio * initalY;
}
