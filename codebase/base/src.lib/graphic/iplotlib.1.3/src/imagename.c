/* imagename.c
   =========== 
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




int PlotImageName(struct Plot *ptr,
	      struct PlotMatrix *matrix,
	      char *name,int w,int h,int d,
	      unsigned  char mask,
              float x,float y,int sflg) {

  if (ptr==NULL) return -1;
  if (ptr->imagename.func==NULL) return 0;
  return (ptr->imagename.func)(ptr->imagename.data,matrix,name,w,h,d,
                               mask,x,y,sflg);
} 

