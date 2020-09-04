/*
Compartmentalized  client sending char-buffers  to server

Modified: Jan Balewski, September, 2014
The port number used in 51717.
The server waits for a connection request from a client.

Note, server1,2 are compatible with client1,2

*/

#include <stdio.h>

#include "JanSocket.h"
#define BufLen 32

//===========================================
int main(int argc, char *argv[]){
  int portno = 51717;
  char *serverIp = (char*)"172.16.185.1"; 
  
  if (argc >1 ) serverIp = argv[1];
  if (argc >2 ) portno =  atoi(argv[2]); 
  
  printf( "%s contacting %s on port %d\n", argv[0], serverIp, portno );
  JanSocket jSoc;  
  jSoc.createClient(serverIp, portno);
  
  printf("OK, staring data transmission ...\n");
  
  int n;
  char buf1[BufLen]; 
  for ( n = 6; n < 10; n++ ) {
    //..... pack output data
    sprintf(buf1,"%d",n);
    jSoc.writeData(buf1,BufLen-1);
    
    //....  wait  for reponse from server
    int n=jSoc.readData(buf1,BufLen-1);

    // .... unpack input data
    buf1[n] = '\0';
    int idata=atoi(buf1);  
    printf("sent %d -> got  %d\n",n, idata );
  }
  
  //...... stop the server by sending '-2'
  jSoc.writeData((char*)"-2",3);
  jSoc.closeSocket();
  
  printf("--- end of client\n");
  return 0;
}

