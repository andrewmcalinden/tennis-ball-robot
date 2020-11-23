#include "encodersInClass.h"

int EncoderL::position = 0;
unsigned char EncoderL::state = 0;

int EncoderR::position = 0;
unsigned char EncoderR::state = 0;
int main()
{
    EncoderL::begin();
    EncoderR::begin();
    while(true)
    {
        printEncoders();
    }
}