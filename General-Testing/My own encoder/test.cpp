#include "encoder.h"
#include <iostream>

int main()
{
    Encoder enc(2, 3);
    Encoder enc2(0, 7);
    while (true)
    {
        std::cout << enc.read() << "\n";
    }
}