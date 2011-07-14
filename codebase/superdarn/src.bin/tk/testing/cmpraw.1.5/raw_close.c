/* raw_close.c
   ===========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "rtypes.h"
#include "rtime.h"
#include "lmt.h"
#include "raw.h"
#include "raw_read.h"



void raw_close(struct rawfp *fp) {
  if (fp==NULL) return;
  if (fp->rawfp !=-1) close(fp->rawfp);
}
