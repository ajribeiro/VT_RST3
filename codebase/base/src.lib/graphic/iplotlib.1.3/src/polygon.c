/* polygon.c
   ========= 
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




int PlotPolygon(struct Plot *ptr,struct PlotMatrix *matrix,
                 float x,float y,
                 int num,float *px,float *py,int *t,int fill,
                 unsigned int color,unsigned char mask,float width,
                 struct PlotDash *dash) {

  if (ptr==NULL) return -1;
  if (ptr->polygon.func==NULL) return 0;
  return (ptr->polygon.func)(ptr->polygon.data,matrix,x,y,num,px,py,t,
                             fill,color,mask,width,dash);
} 

