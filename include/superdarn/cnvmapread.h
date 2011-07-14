/* cnvmapread.h 
   ============
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef _CNVMAPREAD_H
#define _CNVMAPREAD_H

int CnvMapRead(int fd,struct CnvMapData *map,struct GridData *grd);
int CnvMapFread(FILE *fp,struct CnvMapData *map,struct GridData *grd);

#endif









