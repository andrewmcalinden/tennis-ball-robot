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
 #include <netinet/in.h>
 #include <arpa/inet.h>
 #include <netdb.h>
//jan
#define MAXHOSTNAME 32
#include <signal.h>
#endif

#ifdef _WIN32
#define close(sockdep) closesocket(sockdep)
#define perror(errmsg) { fprintf(stderr, "%s: %d\n", (errmsg), WSAGetLastError()); }
#endif

#define net_assert(err, errmsg) { if ((err)) { perror(errmsg); assert(!(err)); } }

#define SERVER "localhost"  // must be this or it will not connetc to server
#define PORT 4897
#define BLEN 128

int
main(int argc, char *argv[]) {  // [ port# ]
  struct sockaddr_in server,self;
  struct hostent *sp, *cp;
  int sd;
  int n;
  char buf[BLEN];

#ifdef _WIN32
  int err;
  WSADATA wsa;
  extern int write();  
  err = WSAStartup(MAKEWORD(2,2), &wsa);  // winsock 2.2
  net_assert(err, "sample client: WSAStartup");
#endif

  /*** get TCPClient1 Host information, NAME and INET ADDRESS ***/
  char ThisHost[ MAXHOSTNAME];
  gethostname(ThisHost, MAXHOSTNAME);
  printf("----TCP/Client running at host NAME: %s and PID=%d\n", ThisHost,getpid());
  cp = gethostbyname(ThisHost);
  bcopy ( cp->h_addr, &(self.sin_addr), cp->h_length);
  printf(" (TCP/Client INET ADDRESS is: %s )\n", inet_ntoa(self.sin_addr));
 
  
  sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  // no bind() ??Jan

  /** get TCPServer1 Host information, NAME and INET ADDRESS */
  memset((char *) &server, 0, sizeof(struct sockaddr_in));
  server.sin_family = AF_INET;
  server.sin_port = htons((u_short) PORT);
  sp = gethostbyname(SERVER); 
  printf("----TCP/Server running at host NAME: %s\n", sp->h_name);
  memcpy(&server.sin_addr, sp->h_addr, sp->h_length);
  printf(" (TCP/Server INET ADDRESS is: %s )\n", inet_ntoa(server.sin_addr));
  
  /** Connect to TCPServer1 */
  connect(sd, (struct sockaddr *) &server, sizeof(struct sockaddr_in));
 
  n = recv(sd, buf, sizeof(buf), 0);
  printf("receive n=%d bytes \n",n);
  if(n>0) {
    printf("Connected to ");
  } else {
    printf(" no server found?, expected: \n");
  }
  printf("  TCPServer1: %s:%d\n", inet_ntoa(server.sin_addr), ntohs(server.sin_port));

  if(n<0) exit(1);

  printf("dump content of reced buffer:\n");
  while (n > 0) {
    write(1, buf, n);
    n = recv(sd, buf, sizeof(buf), 0);
  } 

  //  buf="dupa1";send(sd, buf,  sizeof(buf), 0); 
#if 0
  for(;;) {
    printf("Type anything followed by RETURN, or type CTRL-D to exit\n");
    int rc=read(0,buf, sizeof(buf));
    if (rc == 0) break;
    printf(" I'm going to sent back=%s=\n",buf);
    send(sd, buf, rc, 0);
  }
  printf ("EOF... exit\n");
 #endif
  
  close(sd);
  //kill(getppid(), 9);
#ifdef _WIN32
  WSACleanup();
#endif
  exit(0);
 }
