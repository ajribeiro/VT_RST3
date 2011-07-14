/* mlt.h
   =====
   Author: R.J.Barnes
*/

/* 
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#ifndef _MLT_H
#define _MLT_H

double MLTConvertYMDHMS(int yr,int mo,int dy,int hr,int mt,int sc,
                        double mlon);

double MLTConvertYrsec(int yr,int yrsec,double mlon);

double MLTConvertEpoch(double epoch,double mlon);

#endif
