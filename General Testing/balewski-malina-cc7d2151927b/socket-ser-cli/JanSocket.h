
#ifndef JANSOCKET_HH
#define JANSOCKET_HH

#include <sys/socket.h>
#include <arpa/inet.h>  //for inet_ntoa()

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <fcntl.h>

// uint16_t    htons(uint16_t hostshort);
// convert values between host and network byte order

class JanSocket {
 private:
  struct sockaddr_in serv_addr, cli_addr;
  u_short  portno;
  int sockfd, livefd;
  int clilen;
  enum { JanBufLen=32};
  char ThisHostName[ JanBufLen];
  
 public:
  //.......................................
  JanSocket() { 
    /*** get TCPServer1 Host information: NAME and INET ADDRESS ***/
    gethostname(ThisHostName, JanBufLen);
    printf("----TCP/job running at host NAME: %s and PID=%d\n", ThisHostName,getpid());
  } 
 
  //-------------------------------------
  void createClient( char *serverIp, int portnoX) { 
    portno=portnoX;
    struct hostent *cp = gethostbyname(ThisHostName);
    bcopy ( cp->h_addr, &(cli_addr.sin_addr), cp->h_length);
    printf("    (TCP/job=Client, INET ADDRESS is: %s )\n", inet_ntoa(cli_addr.sin_addr ));
 
    struct hostent *server;
    if ( ( server = gethostbyname(  serverIp) ) == NULL ) 
      {perror( "ERROR, server IP not found by client\n" ); exit(1);}
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
      { perror(  "ERROR opening socket by client" ); exit(1);}

    if ( connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
      { perror(  "ERROR connecting to server socket" ); exit(1);}

    livefd=sockfd; // this looks messy,but allows this class to be used by the server & by client

    /*** print server information ***/
    printf("opened new communication with server  %s\n ready to I/O data ...\n", inet_ntoa(serv_addr.sin_addr));
  }
 

  //-------------------------------------
  void createServer( int portnoX) { 
    portno=portnoX;
    
    struct hostent *sp = gethostbyname(ThisHostName);
    bcopy ( sp->h_addr, &(serv_addr.sin_addr), sp->h_length);
    printf("    (TCP/job=Server, INET ADDRESS is: %s )\n", inet_ntoa(serv_addr.sin_addr));
    
    /*** Construct name of socket ***/
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons( portno );//On big endian computers these functions simply return their arguments.
    //Computer networks are big endian.
    // Little endian computers include the intel series (80486, pentium etc)
    
    /*** Create socket on which to send  and receive ***/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { perror(  "ERROR opening socket" );   exit(1); }
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
      { perror(  "ERROR on binding"  );   exit(1); }
    //binds a socket to an address of the current host and port number on which the server will run
    //This can fail for a number of reasons, the most obvious being that this socket is already in use on this machine.
    
    listen(sockfd,5);  //the second is the size of the backlog queue, i.e., the number of connections that can be waiting while the process is handling a particular connection. 
    
    clilen = sizeof(cli_addr);
    printf("JanSocket is listening ...\n");
  }
  
  //-------------------------------------
  void acceptClient(){
    if ( ( livefd = accept( sockfd, (struct sockaddr *) &cli_addr, (socklen_t*) &clilen) ) < 0 )
      {perror( "ERROR on accept" );   exit(1); }
    /* The accept() system call causes the process to block until a client connects to the server.
       Thus, it wakes up the process when a connection from a client has been 
       successfully established. 
       It returns a new file descriptor, and all communication on this connection should be done using the new file descriptor. 
    */
    
    /*** print client information ***/
    printf("opened new communication with client  %s\n ready to I/O data ...\n", inet_ntoa(cli_addr.sin_addr));
  }


  //-------------------------------------
  void dropClient(){
    close( livefd ); 
    livefd =-1;
 }

  //-------------------------------------
  void closeSocket(){
    close( sockfd );
    sockfd=livefd =-2; 
  }
  
  //----------------------------
  int readData(char *buf, int len){
    int n;
    if ( (n = read(livefd,buf,len) ) < 0 ) {
      perror(  "ERROR reading from socket");   exit(1);  }
    return n;
  }
  
  //----------------------------
  void writeData(char *buf, int len){
    if (  write( livefd, buf, len )  < 0 ) {
      perror( "ERROR writing  to socket"  );  exit(1);
    }
  }
};

#endif
