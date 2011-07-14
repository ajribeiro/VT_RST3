/* simread.h
   ========= 
   Author: R.J.Barnes
*/


/* 
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef _simread_H
#define _simread_H


int SimDecode(struct DataMap *ptr,struct SimData *sim);
int SimFread(FILE *fp,struct RadarParm *,struct SimData *);
int simread(int fid,struct RadarParm *,struct SimData *);

#endif
