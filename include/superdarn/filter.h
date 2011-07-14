/* filter.h
   ======= 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#ifndef _FILTER_H
#define _FILTER_H

#define MAX_BEAM 256
#define FILTER_WIDTH 3
#define FILTER_HEIGHT 3
#define FILTER_DEPTH 3

int FilterRadarScan(int mode,int depth,int inx,struct RadarScan **src,
                    struct RadarScan *dst,int prm);


#endif
