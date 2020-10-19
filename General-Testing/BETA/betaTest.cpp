#include "encoderL.h"
#include<iostream>

int EncoderL::position = 0;
unsigned char EncoderL::state = 0;

int main()
{
    EncoderL::begin();
    while(true)
    {
        std::cout << EncoderL::read() << "\n";
    }
}