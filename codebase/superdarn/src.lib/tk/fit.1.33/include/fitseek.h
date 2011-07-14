/* fitseek.h
   ========= 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#ifndef _FITSEEK_H
#define _FITSEEK_H

int FitSeek(int fid,
	      int yr,int mo,int dy,int hr,int mt,int sc,double *atme,
	      struct FitIndex *inx);
int FitFseek(FILE *fp,
	    int yr,int mo,int dy,int hr,int mt,int sc,double *atme,
	       struct FitIndex *inx);

#endif
