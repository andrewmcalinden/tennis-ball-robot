#pragma once

void updateLeftEncoder(double reading);
void updateRightEncoder(double reading);

void setPose(double x, double y, double theta); //theta in degrees
void updatePos(double leftReading, double rightReading);

bool epsilonEquals();

double getX();
double getY();
double getHeading();