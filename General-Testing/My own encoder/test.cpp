#include "encoder.h"
#include <iostream>

int main()
{
    Encoder enc(7, 0);
    Encoder enc(2, 3);
    while (true)
    {
        std::cout << enc.read() << "\n";
    }
}