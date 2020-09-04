/* A simple server in the internet domain using TCP,
Accepts input data from client, performs computation (y=2*x), and returns results back to client

Author D. Thiebaut
Adapted from http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html

Modified: Jan Balewski, September, 2014

The port number used in 51717.
This code is compiled and run on the Raspberry as follows:
   
    g++ -o server server.c 
    ./server

The server waits for a connection request from a client.
The server assumes the client will send positive integers, which it sends back multiplied by 2.
If the server receives -2, it exits.

Note, server1,2 are compatible with client1,2
*/

#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

//jan 
#include <arpa/inet.h>  //for inet_ntoa()
#define BufLen 32

//===========================================
void error( char *msg ) {
  perror(  msg );  exit(1);
}

//===========================================
int func( int a ) {
   return 2 * a+50;
}

//===========================================
void sendDataI( int sockfd, int x ) {
  int n;
  char buffer[BufLen];
  sprintf( buffer, "%d\n", x );
  if ( (n = write( sockfd, buffer, strlen(buffer) ) ) < 0 ) {
    sprintf( buffer, "ERROR writing  %d to socket \n", x );
    error( buffer );
  }
} 

//===========================================
int getDataI( int sockfd ) {
  char buffer[BufLen];
  int n;

  if ( (n = read(sockfd,buffer,BufLen-1) ) < 0 ) {
    sprintf( buffer, "ERROR reading from socket , n=%d \n", n );
    error(  buffer);
  }
  buffer[n] = '\0';
  return atoi( buffer );
}

//===========================================
int main(int argc, char *argv[]) {
     int sockfd, livefd;
     u_short  portno = 51717;
     struct sockaddr_in serv_addr, cli_addr;
     
     // uint16_t    htons(uint16_t hostshort);
     // convert values between host and network byte order

     if (argc >1 ) portno =  atoi(argv[1]); 

     printf( "use: %s  port #%d  \n", argv[0], portno);
     
     /*** get TCPServer1 Host information: NAME and INET ADDRESS ***/
     char ThisHost[ BufLen];
     gethostname(ThisHost, BufLen);
     printf("----TCP/Server running at host NAME: %s and PID=%d\n", ThisHost,getpid());
     struct hostent *sp = gethostbyname(ThisHost);
     bcopy ( sp->h_addr, &(serv_addr.sin_addr), sp->h_length);
     printf("    (TCP/Server INET ADDRESS is: %s )\n", inet_ntoa(serv_addr.sin_addr));

     /*** Construct name of socket ***/
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons( portno );//On big endian computers these functions simply return their arguments.
     //Computer networks are big endian.
     // Little endian computers include the intel series (80486, pentium etc)


     /*** Create socket on which to send  and receive ***/
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) error(  "ERROR opening socket" );
     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
       error(  "ERROR on binding"  );
     //binds a socket to an address of the current host and port number on which the server will run
     //This can fail for a number of reasons, the most obvious being that this socket is already in use on this machine.

     listen(sockfd,5);  //the second is the size of the backlog queue, i.e., the number of connections that can be waiting while the process is handling a particular connection. 


     /*** accept TCP connections from client */     
     while ( 1 ) {
       printf( "waiting for new client...\n" );
       int clilen = sizeof(cli_addr);
       if ( ( livefd = accept( sockfd, (struct sockaddr *) &cli_addr, (socklen_t*) &clilen) ) < 0 )
	 error( "ERROR on accept" );
       /* The accept() system call causes the process to block until a client connects to the server.
	  Thus, it wakes up the process when a connection from a client has been 
	  successfully established. 
	  It returns a new file descriptor, and all communication on this connection should be done using the new file descriptor. 
       */

       /*** print client information ***/
       printf("opened new communication with client  %s\n wating for data ...\n", inet_ntoa(cli_addr.sin_addr));
       
       while ( 1 ) {
	 int idata = getDataI( livefd );
	 printf( "got idata=%d\n", idata );
	 if ( idata < 0 )  break; // unexpected input data
	 if ( idata == -2 )   break; //--- if -2 sent by client, we can quit as well 
 	 
	 int idata2 = func( idata ); // server computes result based on input
	
	 printf( "sending back to client %d\n", idata2 );
	 sendDataI( livefd, idata2 );
       }
       close( livefd ); 
       break;
     }
     return 0; 
}
