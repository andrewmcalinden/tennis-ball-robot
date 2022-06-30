#include <wiringPi.h>

#define GPIO_NUM	3
#define DELAY_DOT	200
#define DELAY_DASH	550
#define DELAY_GAP	500

void do_blink(int length);

int main()
{
	int i;
    wiringPiSetup();
    pinMode(GPIO_NUM, OUTPUT);
    while (true)
    {
        for (i=0;i<3;i++)
        {
            do_blink(DELAY_DOT);
        }
        delay(DELAY_GAP);
        for (i=0;i<3;i++)
        {
            do_blink(DELAY_DASH);
        }
        delay(DELAY_GAP);
        for (i=0;i<3;i++)
        {
            do_blink(DELAY_DOT);
        }
        delay(DELAY_GAP<<1);
    }
}

void do_blink(int length)
{
    digitalWrite(GPIO_NUM, HIGH);
	delay(length);
	digitalWrite(GPIO_NUM, LOW);
	delay(length);
}

