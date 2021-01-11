#include <ctime>
#include <iostream>
#include <wiringPi.h>
int main()
{
    std::clock_t timer;
    timer = std::clock();

    const unsigned int delayAmount = 1000;

    while(true)
    {
        std::cout << ((std::clock() - timer) / (double)CLOCKS_PER_SEC) + (delayAmount / 1000.0) << "\n";
        delay(delayAmount);
    }
}