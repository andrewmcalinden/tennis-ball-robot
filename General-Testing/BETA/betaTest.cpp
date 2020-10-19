#include "encoderL.h"
#include<iostream>

int EncoderL::position = 0;
unsigned char EncoderL::state = 0;

int main()
{
    EncoderL enc;
    while(true)
    {
        std::cout << enc.read() << "\n";
    }
}