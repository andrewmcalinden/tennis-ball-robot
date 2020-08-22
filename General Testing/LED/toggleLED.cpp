#include <wiringPi.h>
#include <iostream>

#define LED_OUT 3 //GPIO 22
#define BUTTON_IN 6 //GPIO 25

int main()
{
	wiringPiSetup();
	pinMode(LED_OUT, OUTPUT);
	pinMode(BUTTON_IN, INPUT);

	while (true)
	{
		std::cout << digitalRead(BUTTON_IN) << "\n";
		delay(300);
	}


	/*
	while(true)
	{
		//if button pressed, toggle LED
		if(digitalRead(BUTTON_IN) == LOW)
		{
		digitalWrite(LED_OUT, !digitalRead(LED_OUT));
		delay(500);
		}
	}
	*/
}
