/* socket.h
   ========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#define CLIENT_MAX 64
#define BUF_SIZE 10*1024

struct client {
  int sock;
  unsigned char stream;
  int in_sze;
  int out_sze;
  char host[256];
  unsigned char in_buf[BUF_SIZE]; /* data from client */
  unsigned char out_buf[BUF_SIZE]; /* data to client */
};

int createsocket(int *port);
int processsocket(int sock,int inpipe);
int pollsock(int sock,struct timeval *tv,fd_set *fdset);
