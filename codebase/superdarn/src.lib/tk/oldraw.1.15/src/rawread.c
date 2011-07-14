/* rawread.c
   =========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <zlib.h>
#include "rtypes.h"
#include "dmap.h"
#include "rprm.h"
#include "rawdata.h"
#include "lmt.h"
#include "raw.h"
#include "oldrawread.h"



int OldRawRead(struct OldRawFp *fp,struct RadarParm *prm,
               struct RawData *raw) { 
  if (fp==NULL) return -1;
  raw->thr=fp->thr;
  return (fp->rawread)(fp,prm,raw);
}
 
int OldRawReadDataraw(struct OldRawFp *fp,struct RadarParm *prm,
                      struct RawData *raw) {

 /* reads only the power and ACFs without altering the 
    radar parameters */

  struct RadarParm tprm;
  raw->thr=fp->thr;
  if ( (fp->rawread)(fp,&tprm,raw) !=0) return -1;
  prm->noise.mean=tprm.noise.mean;
  prm->tfreq=tprm.tfreq;
 
  return 0;
}




