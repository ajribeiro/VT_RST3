/* plot_mmaxmin.h
   ============== 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




void plot_maxmin(struct Plot *plot,
                 struct CnvGrid *ptr,int magflg,
		 float xoff,float yoff,float wdt,float hgt,float sze,
                 int (*trnf)(int,void *,int,void *,void *data),void *data,
                 unsigned int color,char mask,float width,
                 struct PlotDash *dash);



