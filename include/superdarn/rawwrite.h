/* rawwrite.h
   ========== 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef _RAWWRITE_H
#define _RAWWRITE_H

int RawEncode(struct DataMap *ptr,struct RadarParm *prm,struct RawData *raw);
int RawFwrite(FILE *fp,struct RadarParm *,struct RawData *);
int RawWrite(int,struct RadarParm *,struct RawData *);

#endif
