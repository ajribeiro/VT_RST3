/* rawseek.h
   ========= 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#ifndef _RAWSEEK_H
#define _RAWSEEK_H

int RawSeek(int fid,
	      int yr,int mo,int dy,int hr,int mt,int sc,double *atme,
	      struct RawIndex *inx);
int RawFseek(FILE *fp,
	    int yr,int mo,int dy,int hr,int mt,int sc,double *atme,
	       struct RawIndex *inx);

#endif
