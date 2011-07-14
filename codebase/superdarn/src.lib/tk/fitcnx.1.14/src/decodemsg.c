/* decodemsg.c
   ===========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <zlib.h>
#include "rtypes.h"
#include "dmap.h"
#include "rprm.h"
#include "fitdata.h"
#include "fitread.h"

int FitCnxDecodeIPMsg(struct RadarParm *prm,struct FitData *fit,
                         unsigned char *buffer,int size) {
  struct DataMap *ptr;
  int s;

  ptr=DataMapDecodeBuffer(buffer,size);
  if (ptr==NULL) return 0;
  s=RadarParmDecode(ptr,prm);
  if (s==0) s=FitDecode(ptr,fit);
  DataMapFree(ptr);
  return s;
}







