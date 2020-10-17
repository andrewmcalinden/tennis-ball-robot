#include <wiringPi.h>
#include "encoder.h"

int main()
{
    Encoder enc(7, 0);
    while(true)
    {
        std::cout << end.read() << "\n";
    }
}