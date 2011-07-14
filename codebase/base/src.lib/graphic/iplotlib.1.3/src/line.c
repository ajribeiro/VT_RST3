/* line.c
   ====== 
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




int PlotLine(struct Plot *ptr,
              float ax,float ay,float bx,float by,
              unsigned int color,unsigned char mask,float width,
              struct PlotDash *dash) {

  if (ptr==NULL) return -1;
  if (ptr->line.func==NULL) return 0;
  return (ptr->line.func)(ptr->line.data,ax,ay,bx,by,color,mask,width,dash);
} 



