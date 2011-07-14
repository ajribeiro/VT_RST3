/* fit_read.c
   ==========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




/* This routine reads in and decodes a record from a fit file */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "rtypes.h"
#include "lmt.h"
#include "raw.h"
#include "fit.h"

#include "fit_read.h"

int fit_read(struct fitfp *ptr,struct fitdata *fit_data) {
  if (ptr==NULL) return -1;
  return (ptr->fitread)(ptr,fit_data);
}





