/* cfitclose.c
   ===========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <zlib.h>
#include "rtypes.h"
#include "cfitdata.h"
#include "cfitread.h"




void CFitClose(struct CFitfp *fptr) {
  if (fptr !=NULL) {
    if (fptr->fp !=0) gzclose(fptr->fp);
    if (fptr->fbuf !=NULL) free(fptr->fbuf);
    free(fptr);
  }
}

