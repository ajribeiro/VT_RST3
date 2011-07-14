/* contour.h
   =========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef _CONTOUR_H
#define _CONTOUR_H


#define contour_INT 1
#define contour_FLOAT 2
#define contour_DOUBLE 4

void ContourFree(int cnum,struct PolygonData **ptr);


struct PolygonData **Contour(void *zbuffer,int type,
		            int wdt,int hgt,int cnum,void *cval,
		            int smooth,int flag,int rflag,int bflag);

struct PolygonData **ContourTransform(int cnum,struct PolygonData **src,
                                      int (*trf)(int ssze,void *src,int dsze,
                                                 void *dst,void *data),
                                      void *data);

void ContourModify(int cnum,struct PolygonData **src,
                                      int (*trf)(int ssze,void *src,int dsze,
                                                 void *dst,void *data),
		   void *data);

void ContourFree(int cnum,struct PolygonData **src);
                 
#endif
