#include <iostream>
#include "encodersInClass.h"
#include "../BETA/encoderL.h"
#include "../BETA/encoderR.h"
void Encoders::printEncoders()
{
    std::cout << "L: " << EncoderL::read();
    std::cout << "\tR: " << EncoderR::read() << "\n";
}