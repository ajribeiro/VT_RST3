/* pipe.c
   ======
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "connex.h"





int pipewrite(int fildes,char st,
	      unsigned char *buffer,unsigned int size) {
  int byte;
  int cnt=0;
  int hsze=0;

  char hdr[sizeof(int)+1]; 

  hdr[0]=st;
  *((int *)(hdr+1))=size;
 
  hsze=sizeof(int)+1;
  while (cnt<hsze) { 
    byte=write(fildes,hdr+cnt,hsze-cnt);
    if (byte<=0) {
      ConnexErr=MSGERR_PIPE_CLOSED;
      break;
    }
    cnt+=byte;
  }
  if (cnt<hsze) return -1;

  cnt=0;  /* write out the message */
  while (cnt<size) {
    byte=write(fildes,buffer+cnt,size-cnt); 
    if (byte<=0) {
      ConnexErr=MSGERR_PIPE_CLOSED;
      break;
    }
    cnt+=byte;
  }
  if (cnt<size) return -1;
  return size;
}  


int piperead(int fildes,unsigned char **buffer,unsigned char *st) {

  int byte;
  int cnt=0;

  int hsze=sizeof(int)+1;
  char hdr[sizeof(int)+1];

  unsigned int size;   

  while (cnt<hsze) { 
    byte=read(fildes,hdr,hsze);
    if (byte<=0) {
       ConnexErr=MSGERR_PIPE_CLOSED;
       break;
    }
    cnt+=byte;
  }
  if (cnt<hsze) return -1;
 
  *st=hdr[0];
  size=*((int *) (hdr+1));


  if (size==0) {
    if (*buffer !=NULL) free(*buffer);
    *buffer=NULL;
    return 0;
  }

  if (*buffer !=NULL) {  
    unsigned char *tmp;  
    if ((tmp=realloc(*buffer,size)) ==NULL) {
      ConnexErr=MSGERR_NOMEM;
      return -1;
    }
    *buffer=tmp;
  } else {
    if ((*buffer=malloc(size)) ==NULL) {
      ConnexErr=MSGERR_NOMEM;
     return -1;
    }
  }

 
  cnt=0;  /* read in the message */
  while (cnt<size) {
    byte=read(fildes,(*buffer)+cnt,size-cnt); 
    if (byte<=0) {
      ConnexErr=MSGERR_PIPE_CLOSED;
      break;
    }
    cnt+=byte;
  }
 
  if (cnt<size) {
     free(*buffer);
     *buffer=NULL;
     return -1;
  }
 
  return size;
}  
