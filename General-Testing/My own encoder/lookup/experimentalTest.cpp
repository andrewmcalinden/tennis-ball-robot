#include "experimentalEncoder.h"
#include <iostream>
int main()
{
    ExperimentalEncoder enc2(2, 3);
    ExperimentalEncoder enc1(0, 7);
    while (true)
    {
        std::cout << "read1: " << enc1.read() << "  read2: " << enc2.read() << "\n";
    }
}