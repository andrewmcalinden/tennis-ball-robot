#include "encoderL.h"
#include<iostream>
#include<cmath>

int EncoderL::position = 0;
unsigned char EncoderL::state = 0;

int main()
{
    EncoderL::begin();
    while(true)
    {
        std::cout << "Left: " << (EncoderL::read()/1440)*2.04*M_PI) << "\n";
        std::cout << "Boomer \n";
    }
}