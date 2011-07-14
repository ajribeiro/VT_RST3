/* image.c
   ======= 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rfbuffer.h"
#include "iplot.h"




int PlotImage(struct Plot *ptr,
	      struct PlotMatrix *matrix,
              struct FrameBuffer *img,
	      unsigned  char mask,
              float x,float y,int sflg) {

  if (ptr==NULL) return -1;
  if (ptr->image.func==NULL) return 0;
  return (ptr->image.func)(ptr->image.data,matrix,img,mask,x,y,sflg);
} 

