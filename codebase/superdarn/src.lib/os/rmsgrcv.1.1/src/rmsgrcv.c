/* rmsgrcv.c
   ========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include "rtypes.h"
#include "rmsg.h"
#include "tcpipmsg.h"

char RMsgRcvDecodeOpen(int sock,size_t *size,unsigned char **store) {

  int s;
  size_t buflen=0;
  unsigned char *bufadr=NULL;

  s=TCPIPMsgRecv(sock,&buflen,sizeof(size_t));
  if (s !=sizeof(size_t)) return TASK_ERR;
  bufadr=malloc(buflen+1); 

  if (bufadr==NULL) return TASK_ERR;
  s=TCPIPMsgRecv(sock,bufadr,buflen);


  if (s !=buflen) {
    free(bufadr);
    return TASK_ERR;
  } 

  *store=bufadr;
  *size=buflen;
  return TASK_OK;
}

char RMsgRcvDecodeData(int sock,struct RMsgBlock *blk,
		       unsigned char **store) {
  int s;
  int i;
  unsigned char *dptr;
  
  blk->num=0;

  s=TCPIPMsgRecv(sock,&blk->num,sizeof(int));
  if (s !=sizeof(int)) return TASK_ERR;
  s=TCPIPMsgRecv(sock,&blk->tsize,sizeof(size_t));
  if (s !=sizeof(size_t)) return TASK_ERR;
  s=TCPIPMsgRecv(sock,&blk->data,sizeof(struct RMsgData)*blk->num);
  if (s !=sizeof(struct RMsgData)*blk->num) return TASK_ERR;
  if (*store !=NULL) {
    free(*store);
    *store=NULL;
  }  

  if (blk->tsize==0) return TASK_OK;

  *store=malloc(blk->tsize);
  if (*store==NULL) return TASK_ERR;
   
    s=TCPIPMsgRecv(sock,*store,blk->tsize);
  if (s !=blk->tsize) return TASK_ERR;

  dptr=*store;
  for (i=0;i<blk->num;i++) {
    blk->ptr[i]=dptr;
    dptr+=blk->data[i].size;
  }
  return TASK_OK;
}

