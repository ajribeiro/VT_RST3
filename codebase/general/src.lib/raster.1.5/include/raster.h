/* raster.h
   ========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#ifndef _RASTER_H
#define _RASTER_H

#define raster_INT 1
#define raster_FLOAT 2
#define raster_DOUBLE 4

void *Raster(int wdt,int hgt,int sparse,int type,void *zero,
             int poly,float *pnt,int *vertex,void *value);  

void *RasterHigh(int wdt,int hgt,int sparse,int type,void *zero,
             int poly,double *pnt,int *vertex,void *value);  



#endif
