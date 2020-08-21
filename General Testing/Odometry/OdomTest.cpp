#include<iostream>
#include "Odometry.h"

int main()
{
    updatePos();
    std::cout << getX() << ", " << getY() << " " << getHeading();
}
