/* plot_extra.c
   ============ 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include "rtypes.h"
#include "rfbuffer.h"
#include "iplot.h"
#include "rtime.h"
#include "text_box.h"
#include "rfile.h"
#include "griddata.h"
#include "cnvmap.h"



void plot_extra(struct Plot *plot,
                float xoff,float yoff,
	        struct CnvMapData *ptr,
                unsigned int color,unsigned char mask,
                char *fontname,float fontsize,
                void *txtdata) {

  char txt[256];
  float txbox[3];
  float lhgt;

  sprintf(txt,"Xy");
  txtbox(fontname,fontsize,strlen(txt),txt,txbox,txtdata);
  lhgt=4+txbox[2]-txbox[1];

  sprintf(txt,"order=%d",ptr->fit_order);
  PlotText(plot,NULL,fontname,fontsize,xoff,yoff,
            strlen(txt),txt,color,mask,1);
  sprintf(txt,"lat. bnd.=%g",ptr->latmin);
  PlotText(plot,NULL,fontname,fontsize,xoff,yoff+lhgt,
            strlen(txt),txt,color,mask,1);

  if (ptr->error_wt !=0) strcpy(txt,"err wt/");
  else strcpy(txt,"");
  if (ptr->model_wt !=0) strcat(txt,"norm mod wt");
  else strcat(txt,"fix mod wt");
  PlotText(plot,NULL,fontname,fontsize,xoff,yoff+2*lhgt,
            strlen(txt),txt,color,mask,1);
  sprintf(txt,"%s %d.%.2d",ptr->source,ptr->major_rev,ptr->minor_rev);
  PlotText(plot,NULL,fontname,fontsize,xoff,yoff+3*lhgt,
            strlen(txt),txt,color,mask,1);



  
}
  
