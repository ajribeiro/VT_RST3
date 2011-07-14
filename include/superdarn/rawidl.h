/* rawidl.h
   ======== 
   Author R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#ifndef _RAWIDL_H
#define _RAWIDL_H


struct RawIDLData {
  struct {
    IDL_LONG major;
    IDL_LONG minor;
  } revision;
  
  float thr;
  float pwr0[MAX_RANGE];
  float acfd[MAX_RANGE*LAG_SIZE*2];
  float xcfd[MAX_RANGE*LAG_SIZE*2];

};

struct RawIDLInx {
  double time;
  IDL_LONG offset;
};

void IDLCopyRawDataToIDL(int nrang,int mplgs,int xcf,struct RawData *raw,
			 struct RawIDLData *iraw);

void IDLCopyRawDataFromIDL(int nrang,int mplgs,int xcf,struct RawIDLData *iraw,
                           struct RawData *raw);

struct RawIDLData *IDLMakeRawData(IDL_VPTR *vptr);

struct RawIDLInx *IDLMakeRawInx(int num,IDL_VPTR *vptr);


#endif
