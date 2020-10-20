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
        std::cout << "\nX: ";
        printf("%.2f", getX());
        std::cout << "  Y: ";
        printf("%.2f", getY());
        std::cout << "  Heading: ";
        printf("%.2f", getHeading());
    }
}
