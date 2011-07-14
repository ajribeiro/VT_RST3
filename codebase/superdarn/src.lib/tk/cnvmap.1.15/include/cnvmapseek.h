/* cnvmapseek.h
   ============
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef _CNVMAPSEEK_H
#define _CNVMAPSEEK_H

int CnvMapSeek(int fid,
	     int yr,int mo,int dy,int hr,int mt,int sc,double *atme,
	     struct CnvMapIndex *inx);
int CnvMapFseek(FILE *fp,
	      int yr,int mo,int dy,int hr,int mt,int sc,double *atme,
	      struct CnvMapIndex *inx);

#endif



