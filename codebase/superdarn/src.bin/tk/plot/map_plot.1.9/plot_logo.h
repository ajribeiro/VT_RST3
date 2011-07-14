/* plot_logo.h
   =========== 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/






void plot_logo(struct Plot *plot,
               float xoff,float yoff,float wdt,float hgt,
	       unsigned int color,unsigned char mask,
               char *fontname,float fontsize,
               void *txtdata);

void plot_web(struct Plot *plot,
               float xoff,float yoff,float wdt,float hgt,
	       unsigned int color,unsigned char mask,
               char *fontname,float fontsize,
	      void *txtdata);

void plot_credit(struct Plot *plot,
               float xoff,float yoff,float wdt,float hgt,
	       unsigned int color,unsigned char mask,
               char *fontname,float fontsize,
		 void *txtdata);

 
