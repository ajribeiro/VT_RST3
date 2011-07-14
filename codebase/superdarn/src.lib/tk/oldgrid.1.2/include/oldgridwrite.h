/* oldgridwrite.h
   ==============
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#ifndef _OLDGRIDWRITE_H
#define _OLDGRIDWRITE_H

int OldGridEncodeOne(FILE *fp,struct GridData *ptr);
int OldGridEncodeTwo(FILE *fp,struct GridData *ptr);
int OldGridEncodeThree(FILE *fp,struct GridData *ptr);
int OldGridFwrite(FILE *fp,struct GridData *ptr);

#endif



