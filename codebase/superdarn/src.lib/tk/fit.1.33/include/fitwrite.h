/* fitwrite.h
   ========== 
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#ifndef _FITWRITE_H
#define _FITWRITE_H

int FitEncode(struct DataMap *ptr,struct RadarParm *prm, struct FitData *fit);
int FitFwrite(FILE *fp,struct RadarParm *,struct FitData *);
int FitWrite(int fid,struct RadarParm *,struct FitData *);

#endif
