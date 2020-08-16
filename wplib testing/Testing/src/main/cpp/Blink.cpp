#include <wiringPi.h>
#include <iostream>
int main()
{
    wiringPiSetup();
    pinMode(0, OUTPUT);
    for (int i = 0; i < 10; i++)
    {
        digitalWrite(0, HIGH);
        delay(1000);
        std::cout << "on";
        digitalWrite(0, LOW);
        delay(1000);
        std::cout << "off"; //test
    }
}
