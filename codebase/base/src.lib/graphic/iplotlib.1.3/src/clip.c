/* clip.c
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




int PlotClip(struct Plot *ptr,
              int num,float *px,float *py,int *t) {
  if (ptr==NULL) return -1;
  if (ptr->clip.func==NULL) return 0;
  return (ptr->clip.func)(ptr->clip.data,num,px,py,t);
} 






