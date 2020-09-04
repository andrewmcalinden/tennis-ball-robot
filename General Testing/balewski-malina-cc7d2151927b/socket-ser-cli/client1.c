/* A simple client program to interact with the myServer.c program on the Raspberry.

Sends some  data to server which  performs computation (y=2*x), and returns results back to client

Author D. Thiebaut
Adapted from http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html

Modified: Jan Balewski, September, 2014
INPUT:  IP of the server


The port number used in 51717.
This code is compiled and run on the Macbook laptop as follows:
   
    g++ -o client client.c 
    ./client

If the server receives -2, it exits.

Note, server1,2 are compatible with client1,2
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

//jan 
#define BufLen 32

//===========================================
void error(char *msg) {
    perror(msg);
    exit(0);
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
  char buffer[32];
  int n;

  if ( (n = read(sockfd,buffer,31) ) < 0 ) {
    sprintf( buffer, "ERROR reading from socket , n=%d \n", n );
    error(  buffer);
  }
  buffer[n] = '\0';
  return atoi( buffer );
}


//===========================================
int main(int argc, char *argv[]){
    int sockfd, portno = 51717;
    char *serverIp = "172.16.185.1";
    struct sockaddr_in serv_addr,cli_addr;
    struct hostent *server;
 
    if (argc >1 ) serverIp = argv[1];
    if (argc >2 ) portno =  atoi(argv[2]); 

    printf( "%s contacting %s on port %d\n", argv[0], serverIp, portno );

    /*** get TCP-Client information: NAME and INET ADDRESS ***/
    char ThisHost[ BufLen];
    gethostname(ThisHost, BufLen);
    printf("----TCP/Client running at host NAME: %s and PID=%d\n", ThisHost,getpid());
    struct hostent *cp = gethostbyname(ThisHost);
    bcopy ( cp->h_addr, &(cli_addr.sin_addr), cp->h_length);
    printf("    (TCP/Client INET ADDRESS is: %s )\n", inet_ntoa(cli_addr.sin_addr ));
    
    if ( ( server = gethostbyname(  serverIp) ) == NULL ) 
      error( "ERROR, server IP not found by client\n" );
    printf("client found server named %s by IP \n",server->h_name);

      
    /*** Construct name of socket ***/
    bzero( (char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    // memcpy(dest, src, len);
    // bcopy (src, dest, len);
    bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    serv_addr.sin_port = htons(portno);
    printf("initiate communication with server_addr %s  serv_name=%s\n", inet_ntoa(serv_addr.sin_addr),server->h_name);

   /*** Create socket on which to send  and receive ***/
    if ( ( sockfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0 )
      error(  "ERROR opening socket by client" );

    if ( connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error(  "ERROR connecting to server socket" );
    printf("OK, staring data transmission ...\n");

    int n;
    for ( n = 0; n < 10; n++ ) {
      sendDataI( sockfd, n );
      int idata = getDataI( sockfd );
      printf("sent %d -> got  %d\n",n, idata );
    }
    sendDataI( sockfd, -2 );

    close( sockfd );
    return 0;
}

/*  Setup on Rpi 
$  sudo nmap -p 1-65535 localhost

Starting Nmap 6.00 ( http://nmap.org ) at 2014-09-12 01:06 UTC
Nmap scan report for localhost (127.0.0.1)
Host is up (0.00015s latency).
Other addresses for localhost (not scanned): 127.0.0.1
Not shown: 65533 closed ports
PORT     STATE SERVICE
22/tcp   open  ssh
6010/tcp open  x11

Nmap done: 1 IP address (1 host up) scanned in 22.66 seconds

 */
