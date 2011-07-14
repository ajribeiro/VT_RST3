/* plot_logo.c
   =========== 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "rfbuffer.h"
#include "iplot.h"
#include "rtime.h"
#include "text_box.h"



#define CREDIT "JHU/APL.Software by R.J.Barnes"


void plot_logo(struct Plot *Plot,
               float xoff,float yoff,float wdt,float hgt,
	       unsigned int color,unsigned char mask,
               char *fontname,float fontsize,
               void *txtdata) {

  char txt[256];
  float txbox[3];
  
  sprintf(txt,"SuperDARN");
  txtbox(fontname,fontsize,strlen(txt),txt,txbox,txtdata);
 
  PlotText(Plot,NULL,fontname,fontsize,xoff,yoff+hgt+txbox[1],
            strlen(txt),txt,color,mask,1);

  
}
  

void plot_web(struct Plot *Plot,
               float xoff,float yoff,float wdt,float hgt,
	       unsigned int color,unsigned char mask,
               char *fontname,float fontsize,
               void *txtdata) {

  char txt[256];
  float txbox[3];
   
  sprintf(txt,"http://superdarn.jhuapl.edu");
  txtbox(fontname,fontsize,strlen(txt),txt,txbox,txtdata);
 
  PlotText(Plot,NULL,fontname,fontsize,xoff+wdt-txbox[0],yoff+hgt+txbox[1],
            strlen(txt),txt,color,mask,1);

  
}
  
void plot_credit(struct Plot *Plot,
               float xoff,float yoff,float wdt,float hgt,
	       unsigned int color,unsigned char mask,
               char *fontname,float fontsize,
               void *txtdata) {

  char txt[256];
  float txbox[3];
 
  sprintf(txt,CREDIT);
  txtbox(fontname,fontsize,strlen(txt),txt,txbox,txtdata);
 
  PlotText(Plot,NULL,fontname,fontsize,xoff,yoff+hgt+txbox[1],
            strlen(txt),txt,color,mask,1);

  
}
  
