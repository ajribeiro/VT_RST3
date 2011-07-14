/* aacgm.h
   =======
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef _AACGM_H
#define _AACGM_H

int AACGMLoadCoefFP(FILE  *fp);
int AACGMLoadCoef(char *fname);
int AACGMInit(int year);
int AACGMConvert(double in_lat,double in_lon,double height,
              double *out_lat,double *out_lon,double *r,
              int flag);
#endif


