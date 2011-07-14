/* rawindex.h
   ========== 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#ifndef _RAWINDEX_H
#define _RAWINDEX_H


struct RawIndex {
  int num;
  double *tme;
  int *inx;
};

void RawIndexFree(struct RawIndex *inx);
struct RawIndex *RawIndexLoad(int fid);
struct RawIndex *RawIndexFload(FILE *fp);
 


#endif
