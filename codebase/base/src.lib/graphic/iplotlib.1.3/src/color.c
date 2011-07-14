/* color.c
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

unsigned int PlotColor(int r,int g,int b,int a) {
  return (a<<24) | (r<<16) | (g<<8) | b;
}


unsigned int PlotColorStringRGB(char *txt) {
  unsigned int colval;
  if (txt==NULL) return 0;
  sscanf(txt,"%x",&colval);
  return colval | 0xff000000;
}

unsigned int PlotColorStringRGBA(char *txt) {
  unsigned int colval;
  if (txt==NULL) return 0;
  sscanf(txt,"%x",&colval);
  return colval;
}


