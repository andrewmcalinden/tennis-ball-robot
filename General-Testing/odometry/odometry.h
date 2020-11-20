#include "vector.h"
#include "../math/mathUtil.h"
#include "../BETA/encoderL.h"
#include "../BETA/encoderR.h"
#include <cmath>
#include <iostream>
#include <cstdlib>

void updateLeftEncoder(double reading);
void updateRightEncoder(double reading);

void setPose(double x, double y, double theta); //theta in degrees
void updatePos(double leftReading, double rightReading);

bool epsilonEquals();

double getX();
double getY();
double getHeading(); //in degrees

double getTotalDist();
