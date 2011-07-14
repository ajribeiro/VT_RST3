/* iq.h
   ============= 
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#ifndef _IQ_H
#define _IQ_H

struct IQ {
  struct { 
    int major;
    int minor;
  } revision;
  int chnnum;
  int smpnum;
  int skpnum;
  int seqnum;
  int tbadtr;
  struct timespec *tval;
  int *atten;
  float *noise;
  int *offset;
  int *size;
  int *badtr;
};


struct IQ *IQMake();
void IQFree(struct IQ *ptr);

int IQSetTime(struct IQ *ptr,int nave,struct timespec *tval);
int IQSetAtten(struct IQ *ptr,int nave,int *atten);
int IQSetNoise(struct IQ *ptr,int nave,float *noise);
int IQSetOffset(struct IQ *ptr,int nave,int *offset);
int IQSetSize(struct IQ *ptr,int nave,int *size);
int IQSetBadTR(struct IQ *ptr,int nave,int *badtr);

void *IQFlatten(struct IQ *ptr,int nave,size_t *size);
int IQExpand(struct IQ *ptr,int nave,void *buffer);

#endif
