/* plot_source.h
   ============= 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/






void plot_source(struct Plot *plot,
		 float xoff,float yoff,
                 char *source,int major,int minor,
  	         unsigned int color,unsigned char mask,
                 char *fontname,float fontsize,
                 void *txtdata);
