/* 
 * Copyright (c) 1997, 2014 University of Michigan, Ann Arbor.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of Michigan, Ann Arbor. The name of the University 
 * may not be used to endorse or promote products derived from this 
 * software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Author: Sugih Jamin (jamin@eecs.umich.edu)
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef _WIN32
 #include <winsock2.h>
 #include <ws2tcpip.h>
#else
 #include <string.h>
 #include <unistd.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <arpa/inet.h>
 #include <netinet/in.h>
 #include <netdb.h>
// #include <limits.h>
//jan
#define MAXHOSTNAME 32
#endif

#ifdef _WIN32
#define close(sockdep) closesocket(sockdep)
#define perror(errmsg) { fprintf(stderr, "%s: %d\n", (errmsg), WSAGetLastError()); }
#endif

#define net_assert(err, errmsg) { if ((err)) { perror(errmsg); assert(!(err)); } }

#define PORT 4897
#define QLEN 100
#define BLEN 256

int visits;

int
main(int argc, char *argv[]){ // [ port# ]
  struct sockaddr_in self, client;
  struct hostent *sp, *cp;
  int sd, td;
  int len;
  char buf[BLEN];

#ifdef _WIN32
  int err;
  WSADATA wsa;
  err = WSAStartup(MAKEWORD(2,2), &wsa);  // winsock 2.2
  net_assert(err, "sample server: WSAStartup");
#endif


  /*** get TCPServer1 Host information: NAME and INET ADDRESS ***/
  char ThisHost[ MAXHOSTNAME];
  gethostname(ThisHost, MAXHOSTNAME);
  printf("----TCP/Server running at host NAME: %s and PID=%d\n", ThisHost,getpid());
  sp = gethostbyname(ThisHost);
  bcopy ( sp->h_addr, &(self.sin_addr), sp->h_length);
  printf("    (TCP/Server INET ADDRESS is: %s )\n", inet_ntoa(self.sin_addr));


  /*** Construct name of socket ***/
  self.sin_family = AF_INET;
  self.sin_addr.s_addr = htonl(INADDR_ANY);
  if (argc == 1)
    self.sin_port = htons((u_short) PORT); 
  else  {
    u_short pn = htons(atoi(argv[1])); 
    self.sin_port =  pn;
  }
  
  /*** Create socket on which to send  and receive ***/
  sd = socket (AF_INET,SOCK_STREAM,0); 


  bind(sd, (struct sockaddr *) &self, sizeof(struct sockaddr_in));
  /*** get port information and  prints it out ***/
  socklen_t length = sizeof(self);
  getsockname (sd, (struct sockaddr *)&self,&length);
  printf("Server Port is: %d\n", ntohs(self.sin_port));

  /*** accept TCP connections from clients */
  listen(sd, QLEN);

  while (1) {
    len = sizeof(struct sockaddr_in);
    td = accept(sd, (struct sockaddr *) &client, (socklen_t *)&len);

    /*** print client information ***/
    cp = gethostbyaddr((char *) &client.sin_addr, sizeof(struct in_addr), AF_INET);
    printf("Connected from %s\n", 
          ((cp && cp->h_name) ? cp->h_name : inet_ntoa(client.sin_addr)));

    visits++;
    sprintf(buf, "The server w/ PID=%d has been contacted %d time(s).\n",getpid(), visits);

    send(td, buf, strlen(buf), 0);
    printf("message sent to client\n");

    sleep(5);
    printf("capture response if any ...\n");
    /***  get data from  clients and print them ***/
    for(;;){
      int rc=recv(td, buf, sizeof(buf), 0);
      if (rc > 0){
	buf[rc]=0; 
	printf("Received: %s\n", buf); 
	printf("From TCP/Client: %s:%d\n", 
	       inet_ntoa(client.sin_addr), ntohs(client.sin_port)); 
	printf("(Name is : %s)\n", cp->h_name); 
      }else { 
	printf("Disconnected..\n"); 
	break;
      }
    }
    
    
  }
  close (sd); 

#ifdef _WIN32
WSACleanup();
#endif
exit(0);
}
