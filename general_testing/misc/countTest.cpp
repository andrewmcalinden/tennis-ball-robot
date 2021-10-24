#include "wiringPi.h"
#include <cstdio>
#include <iostream>
#include <unistd.h>

#define COLLECTOR_PIN 4
#define COUNT_INPUT_PIN 12
#define LEFT_MOTOR_DIR_PIN 22
#define LEFT_MOTOR_POWER_PIN 23
#define RIGHT_MOTOR_DIR_PIN 27
#define RIGHT_MOTOR_POWER_PIN 26

#define INITIAL_X 0
#define INITIAL_Y 0
#define INITIAL_THETA 0

#define L_ENCODER_PIN1 7
#define L_ENCODER_PIN2 0
#define R_ENCODER_PIN1 2
#define R_ENCODER_PIN2 3


using namespace std;

volatile int count = 0;
volatile int oldCount = 0;
volatile int startTime = 0;



void countUp()
{
    if(digitalRead(COUNT_INPUT_PIN == HIGH)){
        startTime = millis();
    }
    else{
        if(millis()-startTime > 10){
            count++;
        }
    }
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
        cout << count;
    }
    digitalWrite(COLLECTOR_PIN, LOW);
}