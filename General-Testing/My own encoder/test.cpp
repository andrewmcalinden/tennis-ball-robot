#include "encoder.h"
#include <iostream>

int main()
{
    Encoder encL(7, 0);
    Encoder encR(2, 3);
    while (true)
    {
        std::cout << "lRead: " << encL.read();
        std::cout << "  rRead: " << encL.read() << "\n";
    }
}