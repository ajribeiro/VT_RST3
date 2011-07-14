/* rtypes.h
   ========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#ifndef _RTYPES_H
#define _RTYPES_H

#ifdef _QNX4

#include <sys/types.h>

typedef pid_t ipcid_t;
typedef short int16;
typedef int int32;
typedef double int64;

#else
  typedef int ipcid_t;



  /* This defines the int16, int32, and int64 types */

  #include <limits.h>
  #ifdef WORD_BIT
    #if WORD_BIT == 16
      typedef int int16;
      typedef long int32;
      typedef double int64;
    #endif
    #if WORD_BIT == 32
      typedef short int16;
      typedef int int32;
      typedef long long int64;
    #endif
  #elif defined LONG_BIT
    #if LONG_BIT == 32
      typedef short int16;
      typedef long int32;
      typedef long long int64;
    #endif
    #if LONG_BIT == 64
      typedef short int16;
      typedef int int32;
      typedef long int64;
    #endif
  #elif defined __INT_BITS__
    #if __INT_BITS__== 16
      typedef int int16;
      typedef long int32;
      typedef double int64;
    #endif
    #if __INT_BITS__== 32
      typedef short int16;
      typedef int int32;
      typedef long long int64;
    #endif
  #endif




#endif

#endif
