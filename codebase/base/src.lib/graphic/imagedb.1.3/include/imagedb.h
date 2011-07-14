/* imagedb.h
   ========= 
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef _IMAGEDB_H
#define _IMAGEDB_H

struct FrameBufferDB {
  int num;
  struct FrameBuffer **img;
};

void FrameBufferDBFree(struct FrameBufferDB *ptr);
struct FrameBufferDB *FrameBufferDBMake();
int FrameBufferDBAdd(struct FrameBufferDB *ptr,struct FrameBuffer *img);
struct FrameBuffer *FrameBufferDBFind(struct FrameBufferDB *ptr,char *name);

#endif




