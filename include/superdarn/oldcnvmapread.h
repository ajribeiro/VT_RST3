/* oldcnvmapread.h 
   ===============
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef _OLDCNVMAPREAD_H
#define _OLDCNVMAPREAD_H

int OldCnvMapFread(FILE *fp,struct CnvMapData *map,struct GridData *grd);
int OldCnvMapFseek(FILE *fp,int yr,int mo,int dy,int hr,int mt,int sc,
               struct RfileIndex *inx,double *aval);


#endif









