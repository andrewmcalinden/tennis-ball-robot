#include "wiringPi.h"
#include <cstdio>
#include <iostream>
#include<unistd.h>

#define COLLECTOR_PIN 4
#define COUNT_INPUT_PIN 12

using namespace std;

volatile int count = 0;
volatile int oldCount = 0;
volatile int startTime = 0;


void countUp()
{
    if(digitalRead(COUNT_INPUT_PIN == HIGH){
        startTime = milis();
    }
    else{
        if(millis()-startTime > 10){
            count++;
        }
    }
}

int main()
{   wiringPiSetup();
    pinMode(COLLECTOR_PIN, OUTPUT);
    pinMode(COUNT_INPUT_PIN, INPUT);
    digitalWrite(COLLECTOR_PIN, HIGH);
    
    wiringPiISR (COUNT_INPUT_PIN, INT_EDGE_BOTH, &countUp);
    
    while(millis() < 10000)
    {
        cout << count;
    }
    digitalWrite(COLLECTOR_PIN, LOW);
}