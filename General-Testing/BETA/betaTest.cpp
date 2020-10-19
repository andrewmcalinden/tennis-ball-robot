#include "encoderL.h"
#include "encoderR.h"
#include<iostream>

int EncoderL::position = 0;
unsigned char EncoderL::state = 0;
int EncoderR::position = 0;
unsigned char EncoderR::state = 0;

int main()
{
    EncoderL::begin();
    while(true)
    {
        std::cout << "Left: " << EncoderL::read() << "\n";
        std::cout << "Right: " << EncoderR::read() << "\n";
    }
}