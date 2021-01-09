#ifndef MATH_UTIL_H
#define MATH_UTIL_H
double angleWrapDeg(double angle);
double angleWrapRad(double angle);
double angleDiff(double angle1, double angle2);

double toRadians(double degrees);
double toDegrees(double radians);

bool epsilonEquals(double value1, double value2);
#endif


