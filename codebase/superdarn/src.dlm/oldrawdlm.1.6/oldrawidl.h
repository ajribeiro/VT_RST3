/* oldrawidl.h
   =========== 
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#ifndef _OLDRAWIDL_H
#define _OLDRAWIDL_H
 
struct OldRawIDLFp {
  int32 rawunit;
  int32 inxunit;
  double ctime;
  double stime;
  int32 frec;
  int32 rlen;
  int32 ptr;
  int32 thr;
  int32 major_rev;
  int32 minor_rev;  

  /* The actual IDL structure has an integer for the next member */

  int (*rawread)(struct OldRawFp *ptr,struct RadarParm *prm,
                 struct RawData *raw);

};

#endif
