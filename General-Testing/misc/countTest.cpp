#include "wiringPi.h"
#include <cstdio>
#include<unistd.h>

#define COLLECTOR_PIN 4
#define COUNT_INPUT_PIN 12

using namespace std;

volatile int count = 0;
volatile int oldCount = 0;

void countUp(){
    oldCount = count;
    count++;    
}

int main()
{   wiringPiSetup();
    pinMode(COLLECTOR_PIN, OUTPUT);
    pinMode(COUNT_INPUT_PIN, INPUT);
    digitalWrite(COLLECTOR_PIN, HIGH);
    
    wiringPiISR (COUNT_INPUT_PIN, INT_EDGE_FALLING, &countUp);
    
    while(millis()<10000){
        if (count > oldCount){
            printf("\r",count);
            oldCount = count;
            }
    }
    digitalWrite(COLLECTOR_PIN, LOW);
    
}