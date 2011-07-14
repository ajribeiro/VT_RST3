/* bound.h
   ======= 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#ifndef _BOUND_H
#define _BOUND_H

int FilterBoundType(struct RadarScan *ptr,int type);
int FilterBound(int prm,struct RadarScan *ptr,double *min,double *max);

#endif
