/* mergeread.h
   =========
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.



*/




#ifndef _MERGEREAD_H
#define _MERGEREAD_H

int MergeDecode(struct DataMap *ptr,struct MergeData *data);
int MergeFread(FILE *fp,struct MergeData *data);
int MergeRead(int fid,struct MergeData *data);


#endif