/* plot.c
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



int PlotPlotStart(struct Plot *ptr,char *name,
                  float wdt,float hgt,int depth) {
  if (ptr==NULL) return -1;
  if (ptr->plot.start.func==NULL) return 0;
  return (ptr->plot.start.func)(ptr->plot.start.data,name,
                                  wdt,hgt,depth);
}

int PlotPlotEnd(struct Plot *ptr) {
  if (ptr==NULL) return -1;
  if (ptr->plot.end.func==NULL) return 0;
  return (ptr->plot.end.func)(ptr->plot.end.data);
}



