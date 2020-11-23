#include<iostream>
#include "odometry.h"
#include "../BETA/encoderL.h"
#include "../BETA/encoderR.h"

int EncoderL::position = 0;
unsigned char EncoderL::state = 0;

int EncoderR::position = 0;
unsigned char EncoderR::state = 0;

int main()
{ 
    EncoderL::begin();
    EncoderR::begin();
    while (true)
    {
        updatePos(EncoderL::read(), EncoderR::read());
        std::cout << "\nX:";
        printf("%.2f", getX());
        std::cout << "  Y:";
        printf("%.2f", getY());
        std::cout << "  Heading:";
        printf("%.2f", getHeading());
        std::cout << "  Total Distance:";
        printf("%.2f", getTotalDist());
    }
}
