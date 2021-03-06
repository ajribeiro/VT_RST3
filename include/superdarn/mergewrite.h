/* mergewrite.h
   ==========
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.



*/




#ifndef _MERGEWRITE_H
#define _MERGEWRITE_H

int MergeEncode(struct DataMap *ptr,struct MergeData *data);
int MergeFwrite(FILE *fp,struct MergeData *data);
int MergeWrite(int fid,struct MergeData *data);

#endif
