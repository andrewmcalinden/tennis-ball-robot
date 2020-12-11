#include <iostream>
#include "motor.h"
#include <wiringPi.h>

using namespace std;

#define LEFTPIN 5
#define RIGHTPIN 6


int main()
{
    wiringPiSetup();

    pinMode(LEFTPIN, INPUT);
    pinMode(RIGHTPIN, INPUT);

    while (true){
        unsigned int timeInit = micros();

        while(digitalRead(LEFTPIN) == 0/*||(micros()-timeInit)<=2041*/){}

        unsigned int timeGap = micros()-timeInit;

        double Lpower = timeGap/2041.0;
        cout << Lpower << "\n";
        while(digitalRead(LEFTPIN) == 1){}
        
    }
}

