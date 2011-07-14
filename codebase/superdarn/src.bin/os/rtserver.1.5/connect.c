/* connect.c
   =========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <sys/uio.h>
#include <errno.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include "errlog.h"
#include "socket.h"

extern struct client client[CLIENT_MAX];
extern int msgmax;

extern char *taskname;
extern int errsock;

void closesock(int i) {
  if ((i<msgmax) && (client[i].sock !=-1)) {
    
    char errbuf[256];
    sprintf(errbuf,"%s : Close Connection.",client[i].host);
    ErrLog(errsock,taskname,errbuf);
    
    close(client[i].sock);
    client[i].sock=-1;
    if (i==msgmax-1) msgmax--;
  } 
}

int opensock(int sock,fd_set *fdset) {
  int i,status;
  char errbuf[256];
  int temp;
  unsigned int clength;
 
  struct sockaddr_in caddr;
 
  if (FD_ISSET(sock,fdset)==0) return -1;
  for (i=0;(i<msgmax) && (client[i].sock !=-1);i++);
  if (i>=CLIENT_MAX) { 
    /* dequeue the request here */
    
    ErrLog(errsock,taskname,"Too many clients attached - refusing connection.");
    
    temp=accept(sock,0,0);
    if (temp !=-1) close(temp);
    return -1;
  }

  clength=sizeof(caddr);
  if ((client[i].sock=accept(sock,
      (struct sockaddr *) &caddr,&clength))==-1) {
    
     ErrLog(errsock,taskname,"Accept failed.");
    
     return -1;
  }

  sprintf(client[i].host,"[%s]",inet_ntoa(caddr.sin_addr));

  if ((status=fcntl(client[i].sock,F_GETFL))==-1) {
    close(client[i].sock);
    client[i].sock=-1;
    
    ErrLog(errsock,taskname,"Failed to read file control block.");
    
    return -1;
  }
  status|=O_NONBLOCK;
  if ((status=fcntl(client[i].sock,F_SETFL,status))==-1) {
    close(client[i].sock);
    client[i].sock=-1;
    
    ErrLog(errsock,taskname,"Failed to write file control block.");
    
    return -1;
  } 
  
  sprintf(errbuf,"%s : Open Connection.",client[i].host);
  ErrLog(errsock,taskname,errbuf);
  
  if (i==msgmax) msgmax++;
  return client[i].sock;
}





