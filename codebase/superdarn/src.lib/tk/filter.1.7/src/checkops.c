/* checkops.c
   ========== 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <math.h>
#include "rtypes.h"
#include "rtime.h"
#include "rawdata.h"
#include "fitdata.h"
#include "scandata.h"
#include "filter.h"




int FilterCheckOps(int depth,struct RadarScan **ptr,int fmax) {
  int bm,bt,num,t;
  for (num=0;num<depth;num++) {
    if (num==depth/2) continue;
    for (bm=0;bm<ptr[depth/2]->num;bm++) {
      bt=ptr[depth/2]->bm[bm].bm;
      for (t=0;t<ptr[num]->num;t++) {
        if (ptr[num]->bm[t].bm !=bt) continue;
        if (ptr[num]->bm[t].frang !=ptr[depth/2]->bm[bm].frang) return -1;
        if (ptr[num]->bm[t].rsep !=ptr[depth/2]->bm[bm].rsep) return -1;
        if ((fmax !=0) && 
           (fabs(ptr[num]->bm[t].freq-ptr[depth/2]->bm[bm].freq)>fmax)) 
           return -1;
      }
    }
  }
  return 0;
}





