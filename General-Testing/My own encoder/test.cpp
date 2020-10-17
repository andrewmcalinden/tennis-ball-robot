#include <wiringPi.h>
#include "encoder.h"

int main()
{
    Encoder enc(7, 2);
    while(true)
    {
        std::cout << end.read() << "\n";
    }
}