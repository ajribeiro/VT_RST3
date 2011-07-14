/* fitcnx.h
   ========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/





#ifndef _FITCNX_H
#define _FITCNX_H

int FitCnxRead(int num,int *sock,struct RadarParm *prm,
                    struct FitData *fit,int *flag,struct timeval *tout); 

#endif









