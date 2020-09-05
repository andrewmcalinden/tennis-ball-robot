#include "motor.h"

class Robot
{
    private:
    Motor l;
    Motor r;

    public:
    void goToPoint(double x, double y, double angle, double power);
}