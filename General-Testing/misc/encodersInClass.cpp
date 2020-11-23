#include "../BETA/encoderL.h"
#include "../BETA/encoderR.h"
void Encoders::startEncoders()
{
    EncoderL::begin();
    EncoderR::begin();
}