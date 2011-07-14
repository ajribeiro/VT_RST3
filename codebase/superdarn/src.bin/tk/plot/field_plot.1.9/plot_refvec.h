/* plot_refvec.h
   ============= 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/





void plot_refvec(struct Plot *plot,float px,float py,int or,double max,
              int magflg,
		 float xoff,float yoff,float wdt,float hgt,float sf,
              int (*trnf)(int,void *,int,void *,void *data),void *data,
              unsigned int color,char mask,float width,
              char *fontname,float fontsize,
              void *txtdata,float rad);

 
