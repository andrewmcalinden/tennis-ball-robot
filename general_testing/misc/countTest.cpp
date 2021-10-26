#include "wiringPi.h"
#include <cstdio>
#include <iostream>
#include <unistd.h>

#define COLLECTOR_PIN 4
#define COUNT_INPUT_PIN 12

//g++ countTest.cpp -lwiringPi -o countTestRun

using namespace std;

volatile int count = 0;
volatile int oldCount = 0;
volatile int startTime = 0;
bool countState = true;


void countUp()
{
    if(countState){
        startTime = millis();
    }
    else{
        if(millis()-startTime > 10){
            count++;
        }
    }
    countState = !countState;
}

int main()
{   
   
    wiringPiSetup();
    pinMode(COLLECTOR_PIN, OUTPUT);
    pinMode(COUNT_INPUT_PIN, INPUT);
    digitalWrite(COLLECTOR_PIN, HIGH);
    
    wiringPiISR (COUNT_INPUT_PIN, INT_EDGE_BOTH, &countUp);
    
    while(millis() < 10000)
    {
        cout << count << endl;
    }
    digitalWrite(COLLECTOR_PIN, LOW);
}