#include<iostream>
#include "Odometry.h"

int main()
{
    double leftReading = 0;
    double rightReading = 0;

    for (int i = 0; i < 100; i++){
        //want to end at 60, so increase by .6
        leftReading += .4;

        //want to end at 40, so increase by .4
        rightReading += .6;

        updatePos(leftReading, rightReading);
    }
    std::cout << getX() << ", " << getY() << " " << getHeading();
}
