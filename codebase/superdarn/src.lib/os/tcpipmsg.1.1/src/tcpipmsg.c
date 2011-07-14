/* tcpipmsg.c
   ==========
   Author: J.Spaleta & R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "tcpipmsg.h"

int TCPIPMsgOpen(char *hostip, int port) {

  /* DECLARE VARIABLES FOR IP CONNECTIONS */

  int sock,temp;
  struct sockaddr_in server;
  struct hostent *hp, *gethostbyname();
  int option;
  socklen_t optionlen;

  sock=socket(AF_INET, SOCK_STREAM, 0);
  if (sock<0) {
    TCPIPMsgErr=OPEN_FAIL;
    return -1;
  }

  server.sin_family=AF_INET;
  hp=gethostbyname(hostip);
  if(hp == 0) {
     TCPIPMsgErr=UNKNOWN_HOST;
     return -1;
  }	
	
  memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
  server.sin_port=htons(port);
  temp=connect(sock, (struct sockaddr *)&server, sizeof(server));
  if(temp < 0) {
    TCPIPMsgErr=CONNECT_FAIL;
    return -1;
  }

  option=TCP_NODELAY;
  optionlen=4;
  temp=setsockopt(sock,6,TCP_NODELAY,&option,optionlen);
  temp=getsockopt(sock,6,TCP_NODELAY,&option,&optionlen);

  optionlen=4;
  option=32768;
  temp=setsockopt(sock,SOL_SOCKET,SO_SNDBUF,&option,optionlen);
  temp=getsockopt(sock,SOL_SOCKET,SO_SNDBUF,&option,&optionlen);

   optionlen=4;
   option=32768;
   temp=setsockopt(sock,SOL_SOCKET,SO_RCVBUF,&option,optionlen);
   temp=getsockopt(sock,SOL_SOCKET,SO_RCVBUF,&option,&optionlen);

   return sock;
}

int TCPIPMsgSend(int fd,void  *buf,size_t buflen) {
  int cc=0,total=0;
  while (buflen > 0) {
    cc = send(fd, buf, buflen, 0);
    if (cc <= 0) return cc;
    buf += cc;
    total += cc;
    buflen -= cc;
  }
  return total;
}

int TCPIPMsgRecv(int fd,void *buf,size_t buflen) {
  int cc=0,total=0;
  while (buflen > 0) {
    cc = recv(fd, buf, buflen, 0);
    if (cc <=0) return cc;
    buf += cc;
    total += cc;
    buflen -= cc;
  }
  return total;
}


