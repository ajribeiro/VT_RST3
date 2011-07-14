/* igrf.h
   ==========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#ifndef _IGRF_H
#define _IGRF_H


int IGRFCall(double date, double flat, double flon, 
         double elev, double *x, double *y, double *z);
 
#endif


