/* bound.c
   ======= 
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
#include "scandata.h"
#include "filter.h"




int FilterBoundType(struct RadarScan *ptr,int type) {
  int bm,rng;
  for (bm=0;bm<ptr->num;bm++) {
    for (rng=0;rng<ptr->bm[bm].nrang;rng++) {
      if (ptr->bm[bm].sct[rng]==0) continue;
      if (ptr->bm[bm].rng[rng].gsct==type) ptr->bm[bm].sct[rng]=0;  
        
    }
  }
  return 0;
}

int FilterBound(int prm,struct RadarScan *ptr,double *min,double *max) {
  int bm,rng;
  for (bm=0;bm<ptr->num;bm++) {
    for (rng=0;rng<ptr->bm[bm].nrang;rng++) {
       
      if (ptr->bm[bm].sct[rng]==0) continue;
     
      if (fabs(ptr->bm[bm].rng[rng].v)<min[0]) ptr->bm[bm].sct[rng]=0;
      if (fabs(ptr->bm[bm].rng[rng].v)>max[0]) ptr->bm[bm].sct[rng]=0;

      if (ptr->bm[bm].rng[rng].p_l<min[1]) ptr->bm[bm].sct[rng]=0;
      if (ptr->bm[bm].rng[rng].p_l>max[1]) ptr->bm[bm].sct[rng]=0;
 
      if (ptr->bm[bm].rng[rng].w_l<min[2]) ptr->bm[bm].sct[rng]=0;
      if (ptr->bm[bm].rng[rng].w_l>max[2]) ptr->bm[bm].sct[rng]=0;

      if (ptr->bm[bm].rng[rng].v_e<min[3]) ptr->bm[bm].sct[rng]=0;
      if (ptr->bm[bm].rng[rng].v_e>max[3]) ptr->bm[bm].sct[rng]=0;
        
   }
  }
  return 0;
}
