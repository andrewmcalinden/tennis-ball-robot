#include <wiringPi.h>
#include <iostream>
int main()
{
    wiringPiSetup();
    pinMode(3, OUTPUT);
    while (true)
    {
        digitalWrite(3, HIGH);
        delay(1000);
        std::cout << "on\n";
        digitalWrite(3, LOW);
        delay(1000);
        std::cout << "off\n"; //test
    }
}
