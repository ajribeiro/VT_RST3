/* rmsgsnd.c
   ========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "rtypes.h"
#include "tcpipmsg.h"
#include "rmsg.h"


int RMsgSndOpen(int sock,size_t buflen,unsigned char *bufadr) {
 
  int s;
  int msg=TASK_OPEN;
   
  s=TCPIPMsgSend(sock,&msg,sizeof(int));
  if (s !=sizeof(int)) return -1;
  s=TCPIPMsgSend(sock,&buflen,sizeof(size_t));
  if (s !=sizeof(size_t)) return -1;

  s=TCPIPMsgSend(sock,bufadr,buflen);
  if (s !=buflen) return -1;
  s=TCPIPMsgRecv(sock,&msg,sizeof(int));

  if (s !=sizeof(int)) return -1;
  if (msg !=TASK_OK) return -1;

  return 0;
}

int RMsgSndClose(int sock) {

  int s;
  int msg=TASK_CLOSE;

  s=TCPIPMsgSend(sock,&msg,sizeof(int));
  if (s !=sizeof(int)) return -1;
  s=TCPIPMsgRecv(sock,&msg,sizeof(int));
  if (s !=sizeof(int)) return s;
  if (msg !=TASK_OK) return -1;
  return 0;
}


int RMsgSndQuit(int sock) {

  int s;
  int msg=TASK_QUIT;

  s=TCPIPMsgSend(sock,&msg,sizeof(int));
  if (s !=sizeof(int)) return -1;
  s=TCPIPMsgRecv(sock,&msg,sizeof(int));
  if (s !=sizeof(int)) return s;
  if (msg !=TASK_OK) return -1;
  return 0;
 


}

int RMsgSndReset(int sock) {

  int s;
  int msg=TASK_RESET;

  s=TCPIPMsgSend(sock,&msg,sizeof(int));
  if (s !=sizeof(int)) return -1;
  s=TCPIPMsgRecv(sock,&msg,sizeof(int));
  if (s !=sizeof(int)) return s;
  if (msg !=TASK_OK) return -1;
  return 0;

  return 0;
}

int RMsgSndSend(int sock,struct RMsgBlock *ptr) {

  int s=0,i;
  int msg=TASK_DATA;

  if (ptr==NULL) return -1;
  if (ptr->num>=MAX_BUF) return -1;
  
  s=TCPIPMsgSend(sock,&msg,sizeof(int));
  if (s !=sizeof(int)) return -1;
  s=TCPIPMsgSend(sock,&ptr->num,sizeof(int));
  if (s !=sizeof(int)) return -1;
  s=TCPIPMsgSend(sock,&ptr->tsize,sizeof(size_t));
  if (s !=sizeof(size_t)) return -1;
  s=TCPIPMsgSend(sock,&ptr->data,sizeof(struct RMsgData)*ptr->num);
  if (s !=sizeof(struct RMsgData)*ptr->num) return -1;

  for (i=0;i<ptr->num;i++) {
    s=TCPIPMsgSend(sock,ptr->ptr[i],ptr->data[i].size);
    if (s !=ptr->data[i].size) break;
  }
  if (i !=ptr->num) return -1;
  s=TCPIPMsgRecv(sock,&msg,sizeof(int));
  if (s !=sizeof(int)) return s;
  if (msg !=TASK_OK) return -1;

  return 0;

}

int RMsgSndAdd(struct RMsgBlock *ptr, 
	       size_t buflen,unsigned char *buf,int type,int tag) {
   if (ptr->num>=MAX_BUF) return -1;  
   ptr->data[ptr->num].type=type;
   ptr->data[ptr->num].tag=tag;
   ptr->data[ptr->num].size=buflen;
   ptr->data[ptr->num].index=ptr->num;
   ptr->ptr[ptr->num]=buf;
   ptr->tsize+=buflen;
   ptr->num++;
   return 0;
}





