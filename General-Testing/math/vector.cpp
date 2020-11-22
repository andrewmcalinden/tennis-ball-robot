#include "vector.h"
#include <cmath>

Vector::Vector(double hor, double vert): x{hor}, y{vert}
{
    magnitude = hypot(x, y);
    angle = atan2(y, x);
}

Vector::Vector(double mag, double angDeg)
{
    magnitude = mag;
    angle = (M_PI / 180.0) * angDeg;
    x = magnitude * cos(angle);
    y = magnitude * sin(angle);

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
