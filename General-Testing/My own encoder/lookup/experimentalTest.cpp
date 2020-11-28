#include "experimentalEncoder.h"
#include <iostream>
#include <wiringPi.h>
int main()
{
    ExperimentalEncoder enc1(2, 3);
    ExperimentalEncoder enc2(0, 7);

    int read1 = 0;
    int pastRead1 = 0;

    int read2 = 0;
    int pastRead2 = 0;
    while (true)
    {
        read1 = enc1.read();
        read2 = enc2.read();
        if (read1 != pastRead1)
        {
            std::cout << "read1: " << read1;
        }
        if (read2 != pastRead2)
        {
            std::cout << "  read2: " << read2;
        }
        std::cout << "\n";
        delay(15);
        pastRead1 = read1;
        pastRead2 = read2;
    }
}