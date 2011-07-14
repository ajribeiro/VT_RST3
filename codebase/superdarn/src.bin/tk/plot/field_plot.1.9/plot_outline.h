/* plot_outline.h
   ============== 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




void plot_outline(struct Plot *plot,struct RadarBeam *sbm,
		  struct GeoLocBeam *gbm,float latmin,int magflg,int maxbeam,
               float xoff,float yoff,float wdt,float hgt,
               int (*trnf)(int,void *,int,void *,void *data),void *data,
	       unsigned int color);

void plot_filled(struct Plot *plot,struct RadarBeam *sbm,
               struct GeoLocBeam *gbm,float latmin,int magflg,
               float xoff,float yoff,float wdt,float hgt,
               int (*trnf)(int,void *,int,void *,void *data),void *data,
	       unsigned int color);

