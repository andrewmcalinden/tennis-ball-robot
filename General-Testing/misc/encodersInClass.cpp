#include <iostream>
#include "encodersInClass.h"
void Encoders::printEncoders()
{
    std::cout << "L: " << EncoderL::read();
    std::cout << "  R: " << EncoderR::read();
}