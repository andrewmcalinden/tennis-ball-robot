#include "encoder.h"
#include <iostream>
int main()
{
    Encoder enc1(0, 7);
    Encoder enc2(5, 8);
    Encoder enc3(2, 3);
    while (true)
    {
        std::cout << "read1: " << enc1.read() << "  read2: " << enc2.read() << "  read3: " << enc3.read() << "\n";
    }
}