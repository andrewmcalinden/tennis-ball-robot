#include <ctime>
#include <iostream>
int main()
{
    std::clock_t timer;
    timer = std::clock();
    while(true)
    {
        std::cout << ((std::clock() - timer) / (double)CLOCKS_PER_SEC);
    }
}