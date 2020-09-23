#include<iostream>
#include <cstdlib>
#include <ctime>

#include "Odometry.h"

int main()
{
    std::clock_t timer;
    timer = std::clock();

    srand((unsigned)time(0));
    while (true)
    {
        double leftReading = rand();
        double rightReading = rand();

        updatePos(leftReading, rightReading);

        double time = ((std::clock() - timer) / (double)CLOCKS_PER_SEC);
        std::cout << time << "\n";
    }
}
