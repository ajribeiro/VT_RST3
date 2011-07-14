/* rawread.h
   ========= 
   Author: R.J.Barnes
*/


/* 
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef _RAWREAD_H
#define _RAWREAD_H


int RawDecode(struct DataMap *ptr,struct RawData *raw);
int RawFread(FILE *fp,struct RadarParm *,struct RawData *);
int RawRead(int fid,struct RadarParm *,struct RawData *);

#endif
