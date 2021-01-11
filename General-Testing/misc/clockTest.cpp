#include <ctime>
#include <iostream>
#include <wiringPi.h>
int main()
{
    std::clock_t timer;
    timer = std::clock();

    const unsigned int delayAmount = 50;

    double time = 0;

    while(true)
    {
        time += ((std::clock() - timer) / (double)CLOCKS_PER_SEC) + (delayAmount / 1000.0);
        //time += (delayAmount / 1000.0);
        std::cout << time << "\n";
        delay(delayAmount);
    }
}