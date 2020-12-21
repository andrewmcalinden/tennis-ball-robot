#include "wiringPi.h"
#include <cstdio>
#include <iostream>
#include<unistd.h>

#define COLLECTOR_PIN 4
#define COUNT_INPUT_PIN 12

using namespace std;

volatile int count = 0;
volatile int oldCount = 0;

void countUp()
{
    count++;
    delay(40);
}

int main()
{   wiringPiSetup();
    pinMode(COLLECTOR_PIN, OUTPUT);
    pinMode(COUNT_INPUT_PIN, INPUT);
    digitalWrite(COLLECTOR_PIN, HIGH);
    
    wiringPiISR (COUNT_INPUT_PIN, INT_EDGE_RISING, &countUp);
    
    while(millis()<10000)
    {
        
        
            cout << count;
            
        
    }
    digitalWrite(COLLECTOR_PIN, LOW);
    
}