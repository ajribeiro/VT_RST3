/* smrscan.h
   =========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef _SMRSCAN_H
#define _SMRSCAN_H

int SmrRadarScan(FILE *fp,int *state,
                 struct RadarScan *ptr,struct RadarParm *prm,
                 struct FitData *fit,int fbeam,
                 int tlen,
                 int lock,int chn);


#endif






