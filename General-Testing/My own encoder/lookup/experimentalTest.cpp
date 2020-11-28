#include "experimentalEncoder.h"
#include <iostream>
int main()
{
    ExperimentalEncoder enc1(2, 3);
    ExperimentalEncoder enc2(0, 7);
    while (true)
    {
        std::cout << "read1: " << enc1.read() << "  read2: " << enc2.read() << "\n";
        delay(15);
    }
}