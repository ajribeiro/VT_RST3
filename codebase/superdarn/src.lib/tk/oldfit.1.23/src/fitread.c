/* fitread.c
   =========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <zlib.h>
#include "rtypes.h"
#include "dmap.h"
#include "rprm.h"
#include "fitdata.h"
#include "oldfitread.h"




int OldFitRead(struct OldFitFp *ptr,struct RadarParm *prm,
               struct FitData *fit) {
  if (ptr==NULL) return -1;
  return (ptr->fitread)(ptr,prm,fit);
}





