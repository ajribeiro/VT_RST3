/* bezier.c
   ======== 
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

int PlotBezier(struct Plot *ptr,
                float x1,float y1,float x2,float y2,
                float x3,float y3,float x4,float y4,
                unsigned int color,unsigned char mask,float width,
                struct PlotDash *dash) {

  if (ptr==NULL) return -1;
  if (ptr->bezier.func==NULL) return 0;
  return (ptr->bezier.func)(ptr->bezier.data,x1,y1,x2,y2,x3,y3,x4,y4,
                     color,mask,width,dash);
} 

