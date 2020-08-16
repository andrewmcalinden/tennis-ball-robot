#include <wiringpi.h>
int main()
{
    wiringPiSetup();
    pinMode(0, OUTPUT);
    for (int i = 0; i < 10; i++)
    {
        digitalWrite(0, HIGH);
        delay(1000);
        digitalWrite(0, LOW);
        delay(1000);
    }
}