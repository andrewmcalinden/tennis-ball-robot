#include <iostream>		// Include all needed libraries here
#include <wiringPi.h>

using namespace std;		// No need to keep using “std”

int main()
{
wiringPiSetup();			// Setup the library
pinMode(8, OUTPUT);		// Configure GPIO0 as an output
pinMode(9, INPUT);		// Configure GPIO1 as an input

// Main program loop
while(true)
{
	// Button is pressed if digitalRead returns 0
	if(digitalRead(9) == true)
{	
	// Toggle the LED
	digitalWrite(8, !digitalRead(8));
delay(500); 	// Delay 500ms
}
}
	return 0;
}
