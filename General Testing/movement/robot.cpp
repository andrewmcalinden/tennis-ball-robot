#include "robot.h"
#include "odometry.h"
#include "mathUtil.h"
#include <cmath>

void Robot::goToPoint(double x, double y, double power)
{
    double distanceToPoint = hypot(x - getX(), y - getY());
    double angleToPointRad = atan2(y - getY(), x - getX()); //distance to turn assuming robot is same angle as point
    double trueAngleToPointRad = angleWrapRad(angleToPointRad - toRadians(getHeading())); //takes into account current robot heading

    //true x and y components accounting for angle difference
    double trueXDistance = cos(trueAngleToPointRad) * distanceToPoint;
    double trueYDistance = sin(trueAngleToPointRad) * distanceToPoint;

    //because these will be very large numbers, we need to convert them into ratios from 0 to 1
    //also need to use power as magnitude (still a %)
    double totalDistance = abs(trueXDistance) + abs(trueYDistance);
    double relativeXPower = (trueXDistance / totalDistance) * power;
    double relativeYPower = (trueYDistance / totalDistance) * power;
}
