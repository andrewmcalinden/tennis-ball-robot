/* 
Compartmentalized  server processing char-buffers  from client

Modified: Jan Balewski, September, 2014
The port number used in 51717.
The server waits for a connection request from a client.

Note, server1,2 are compatible with client1,2
*/

#include <stdio.h>
#include "JanSocket.h"
#define BufLen 32

//===========================================
int main(int argc, char *argv[]) {
  u_short  portno = 51717;
  if (argc >1 ) portno =  atoi(argv[1]); 
  printf( "use: %s  port #%d  \n", argv[0], portno);
  
  JanSocket jSoc;  
  jSoc.createServer( portno);
  
  while ( 1 ) {
    printf( "waiting for new TCP client...\n" );
    jSoc.acceptClient();
    
    printf( "waiting for data from client...\n" );
    char buf1[BufLen];
    while ( 1 ) {
      int n=jSoc.readData(buf1,BufLen-1);
      // .... unpack input data
      buf1[n] = '\0';
      int idata=atoi(buf1);  
      printf( "got idata=%d\n", idata );
      if ( idata < 0 )  break; // unexpected input data
      if ( idata == -2 )   break; //--- if -2 sent by client, we can quit as well 
      
      int idata2 = 3* idata;
      
      //..... re-pack output data
      sprintf(buf1,"%d",idata2);
      printf( "sending back to client %d\n", idata2 );
      jSoc.writeData(buf1,BufLen-1);
    }
    jSoc.dropClient();
    break;
  }
  printf("--- end of server\n");
  return 0; 
}
