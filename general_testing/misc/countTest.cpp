#include "wiringPi.h"
#include <cstdio>
#include <iostream>
#include <unistd.h>

#define COLLECTOR_PIN 4
#define COUNT_INPUT_PIN 12

#define DIRECTION_PIN_FORWARD_LEFT 22
#define POWER_PIN_LEFT 23
#define DIRECTION_PIN_FORWARD_RIGHT 27
#define POWER_PIN_RIGHT 26

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
        if((millis()-startTime) > 20){
            count++;
        }
    }
    countState = !countState;
}
void countUpOG()
{
    count++;
}
int main()
{   
   
    wiringPiSetup();
    pinMode(COLLECTOR_PIN, OUTPUT);
    pinMode(COUNT_INPUT_PIN, INPUT);
    digitalWrite(COLLECTOR_PIN, HIGH);

    pinMode(DIRECTION_PIN_FORWARD_LEFT, OUTPUT);
    pinMode(POWER_PIN_LEFT, PWM_OUTPUT);

    pinMode(DIRECTION_PIN_FORWARD_RIGHT, OUTPUT);
    pinMode(POWER_PIN_RIGHT, PWM_OUTPUT);

    pwmSetClock(1500); //~7khz
    pwmSetRange(100);

    digitalWrite(DIRECTION_PIN_FORWARD_RIGHT, HIGH);
    digitalWrite(DIRECTION_PIN_FORWARD_LEFT, LOW);

    pwmWrite(POWER_PIN_RIGHT, 60);
    pwmWrite(POWER_PIN_LEFT, 60);

    delay(200);
    wiringPiISR (COUNT_INPUT_PIN, INT_EDGE_BOTH, &countUpOG);
    
    delay(1000);
    cout << count << endl;
    delay(1000);
    cout << count << endl;
    delay(1000);
    cout << count << endl;
    delay(1000);
    cout << count << endl;
    delay(1000);
    cout << count << endl;
    delay(1000);
    cout << count << endl;
    delay(1000);
    cout << count << endl;
    delay(1000);
    cout << count << endl;

    digitalWrite(COLLECTOR_PIN, LOW);
    pwmWrite(POWER_PIN_RIGHT, 0);
    pwmWrite(POWER_PIN_LEFT, 0);
}    