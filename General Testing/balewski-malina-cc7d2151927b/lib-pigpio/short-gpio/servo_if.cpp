/*
  servo_if.cpp
  
  gcc -o servo_if servo_if.cpp   -lpigpiod_if  -lrt -lpthread -pthread  
  ./servo_if  (not as sudo)

  make sure daemon: pigpiod is running as sudo

*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <pigpiod_if.h>


int main(int argc, char *argv[]) {
  char hostname[1024];
  hostname[1023] = '\0';
  gethostname(hostname, 1023);
  printf("Hostname: %s\n", hostname);  
  if (strstr(hostname,"rpi")==0){
    printf("host=%s is not R-Pi, app=%s can't access GPIO pins, abort\n",hostname,argv[0]);
    return 3;
  }

  int  status = pigpio_start(0, 0);

  if (status < 0)   {
    fprintf(stderr, "pigpio initialisation failed. Try :\n   ps -ef |grep  pigpiod  \n  sudo pigpiod\n");
    return 1;
  }

  printf("Connected to pigpio daemon.\n");
  int pin=18;
  if ( argc==2) {
    printf("set LED pin to %s \n", argv[1]);
    pin=atoi(argv[1]);
    if(pin<=0) return -3;
  }

  int v;
  //set_mode(pin, PI_OUTPUT);
  v = get_mode(pin);
  printf("pin=%d mode=%d\n",pin,v);
  
  int GPIO=pin;
  printf("PWM/Servo updates servos at 50Hz.  \n pwidth=1500 is in the middle of range\n");
  set_servo_pulsewidth(GPIO, 0);

  for(int k=0;k<10;k++){
    int pwidth=650+200*k; //usec
    set_servo_pulsewidth(GPIO, pwidth);
    printf("pulse width=%d uSec \n",pwidth);  
    time_sleep(1);
    if (k==0) sleep(2);
  }
  set_PWM_dutycycle(GPIO, 0);


  printf("Disconnected from pigpio daemon.\n");

  pigpio_stop();
  return 0;
}
