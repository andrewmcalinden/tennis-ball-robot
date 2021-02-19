#include "vector.h"
#include <cmath>

Vector::Vector(double hor, double vert): x{hor}, y{vert}
{
    magnitude = hypot(x, y);
    angle = atan2(y, x);
}

double Vector::getX()
{
    return x;
}

double Vector::getY()
{
    return y;
}

double Vector::getMagnitude()
{
    return magnitude;
}

double Vector::getAngle()
{
    return angle;
}

Vector Vector::rotated(double angle)
{
    double newX = x * cos(angle) - y * sin(angle);
    double newY = x * sin(angle) + y * cos(angle);
    return Vector(newX, newY);
}
