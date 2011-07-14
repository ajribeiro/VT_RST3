/* fit_close.c
   ===========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




/* This routine reads in and decodes a record from a fit file */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "rtypes.h"
#include "lmt.h"
#include "raw.h"
#include "fit.h"

#include "fit_read.h"
#include "fit_str.h"



void fit_close(struct fitfp *ptr) {
  if (ptr==NULL) return;
  if (ptr->fitfp !=-1) close(ptr->fitfp);
  if (ptr->inxfp !=-1) close(ptr->inxfp);
  if (ptr->fbuf !=NULL) free(ptr->fbuf);
  if (ptr->ibuf !=NULL) free(ptr->ibuf);
  free(ptr);
}



