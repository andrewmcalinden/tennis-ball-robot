#include <cmath>
#include "Vector.h"

Vector::Vector(double hor, double vert): x{hor}, y{vert}{}

double Vector::getX()
{
    return x;
}

double Vector::getY()
{
    return y;
}

Vector Vector::rotated(double angle)
{
    double newX = x * cos(angle) - y * sin(angle);
    double newY = x * sin(angle) + y * cos(angle);
    return Vector(newX, newY);
}
