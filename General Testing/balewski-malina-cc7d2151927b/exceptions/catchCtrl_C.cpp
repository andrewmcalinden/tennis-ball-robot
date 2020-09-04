#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void my_handler(sig_t s){
  printf("my handler caught signal %d\n",(int)s);
           exit(1); 

}

int main(int argc,char** argv)
{
  signal (SIGINT,(__sighandler_t)my_handler);
  printf("now program hangs in while(1) , press ctrl-c to kill it and execute my command\n");

   while(1);
   return 0;

}
