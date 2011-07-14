/* user.c
   ====== 
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include "rfbuffer.h"



int FrameBufferSetUser(struct FrameBuffer *ptr,
                       int (*pixel)(int wdt,int hgt,unsigned char *img,
		       unsigned char *msk,
                       int x,int y,int depth,int off,int sze,
                       unsigned char r,unsigned char g,unsigned char b,
		       unsigned char a,void *data),void *data) {
  if (ptr==NULL) return -1;
  ptr->user.pixel=pixel;
  ptr->user.data=data;
  return 0;
}
