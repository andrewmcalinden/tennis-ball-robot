#include<iostream>
#include "odometry.h"
#include "../BETA/encoderL.h"
#include "../BETA/encoderR.h"

int main()
{
    EncoderL::begin();
    EncoderR::begin();
    while (true)
    {
        updatePos(EncoderL::read(), EncoderR::read());
        std::cout << "X: " << getX() << "Y: " << getY() << "Heading: " << getHeading();
    }
}
