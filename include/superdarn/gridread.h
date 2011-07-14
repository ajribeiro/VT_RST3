/* gridread.h
   ==========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef _GRIDREAD_H
#define _GRIDREAD_H

int GridRead(int fid,struct GridData *gp);
int GridFread(FILE *fp,struct GridData *gp);

#endif



