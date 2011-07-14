/* build..h
   ========
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#ifndef _BUILD_H
#define _BUILD_H

void OpsBuildPrm(struct RadarParm *prm,
                 int *ptab,int (*lags)[2]);
void OpsBuildIQ(struct IQ *iq,unsigned int **badtr);
void OpsBuildRaw(struct RawData *raw);


#endif
