
#include "encoderL.cpp"
#include<iostream>
int main()
{
    EncoderL enc;
    while(true)
    {
        std::cout << enc.read() << "\n";
    }
}