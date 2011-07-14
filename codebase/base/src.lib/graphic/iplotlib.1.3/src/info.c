/* info.c
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




int PlotInfoStart(struct Plot *ptr) {
  if (ptr==NULL) return -1;
  if (ptr->info.start.func==NULL) return 0;
  return (ptr->info.start.func)(ptr->info.start.data);
} 

int PlotInfo(struct Plot *ptr,char *buf,int sze) {
  if (ptr==NULL) return -1;
  if (ptr->info.text.func==NULL) return 0;
  return (ptr->info.text.func)(ptr->info.text.data,buf,sze);
}

int PlotInfoEnd(struct Plot *ptr) {
  if (ptr==NULL) return -1;
  if (ptr->info.end.func==NULL) return 0;
  return (ptr->info.end.func)(ptr->info.end.data);
}


