#include "encoder.h"
#include "../motor/motor.h"
#include <iostream>

#define DIRECTION_PIN_FORWARD_LEFT 22
#define POWER_PIN_LEFT 23
#define DIRECTION_PIN_FORWARD_RIGHT 27
#define POWER_PIN_RIGHT 26


int main()
{
    Encoder enc1(0, 7);
    Encoder enc2(3, 2);

    Motor motorL(DIRECTION_PIN_FORWARD_LEFT, POWER_PIN_LEFT);
    Motor motorR(DIRECTION_PIN_FORWARD_RIGHT, POWER_PIN_RIGHT);

    // motorL.setPower(.2);
    // motorR.setPower(-.2);

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
        if (read1 != pastRead1 || read2 != pastRead2)
        {
            std::cout << "\n";
        }
        delay(1);
        pastRead1 = read1;
        pastRead2 = read2;
    }
}