/* plot_vec.h
   ========== 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/





void plot_vec(struct Plot *plot,struct RadarBeam *sbm,
               struct GeoLocBeam *gbm,float latmin,int magflg,
	      float xoff,float yoff,float wdt,float hgt,float sf,
               int (*trnf)(int,void *,int,void *,void *data),void *data,
 	       unsigned int(*cfn)(double,void *),void *cdata,
               unsigned int gscol,unsigned char gsflg,float width,float rad);
