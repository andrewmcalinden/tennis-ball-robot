#include <wiringPi.h>
#include "encoder.h"
#include<iostream>

int main()
{
    Encoder enc(7, 0);
    while(true)
    {
        std::cout << enc.read() << "\n";
    }
}