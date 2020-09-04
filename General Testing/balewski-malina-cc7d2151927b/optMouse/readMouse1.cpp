#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <linux/input.h>
#include <fcntl.h>
#include <X11/Xlib.h>

/* 
Tested on R-pi2 w/ Ubuntu14.04

To compile:
  gcc readMouse1.cpp -lX11

To list all  connected devices:
 cat /proc/bus/input/devices |grep mouse

To enable none-sudo user to access mouse data
 sudo chmod a+r /dev/input/event3

Results with
crw-r--r-- 1 root root 13, 67 Nov 27 19:03 /dev/input/event3

*/

#define MOUSEFILE "/dev/input/event3"

int main(){
  int fd;
  struct input_event ie;
  Display *dpy;
  Window root, child;
  int rootX, rootY, winX, winY;
  unsigned int mask;

  dpy = XOpenDisplay(NULL);
  XQueryPointer(dpy,DefaultRootWindow(dpy),&root,&child,
              &rootX,&rootY,&winX,&winY,&mask); 

  if((fd = open(MOUSEFILE, O_RDONLY)) == -1) {
    perror("opening device");
    exit(EXIT_FAILURE);
  }

  while(read(fd, &ie, sizeof(struct input_event))) {
    if (ie.type == 2) {
      if (ie.code == 0) { rootX += ie.value; }
      else if (ie.code == 1) { rootY += ie.value; }
      printf("time%ld.%06ld\tx %d\ty %d\n", 
	     ie.time.tv_sec, ie.time.tv_usec, rootX, rootY);
    } else if (ie.type == 1) {
      if (ie.code == 272 ) { 
        printf("Mouse button ");
        if (ie.value == 0)  
          printf("released!!\n");
        if (ie.value == 1)  
          printf("pressed!!\n");
      } else {
        printf("time %ld.%06ld\ttype %d\tcode %d\tvalue %d\n",
	       ie.time.tv_sec, ie.time.tv_usec, ie.type, ie.code, ie.value);
      }
    }
  }
  return 0;
}
