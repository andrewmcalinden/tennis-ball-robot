#ifndef ODOMETRY_H
#define ODOMETRY_H
void updateLeftEncoder(double reading);
void updateRightEncoder(double reading);

void setPose(double x, double y, double theta); //theta in degrees
void updatePos(double leftReading, double rightReading);

bool epsilonEquals();

double getX();
double getY();
double getHeading(); //in degrees

extern double globalXPos;
extern double globalYPos;
extern double globalHeading; //in degrees, from -180 to 180
#endif