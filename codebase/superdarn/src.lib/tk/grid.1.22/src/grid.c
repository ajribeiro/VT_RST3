/* grid.c
   ======
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
#include "rtime.h"
#include "dmap.h"
#include "griddata.h"




struct GridData *GridMake() {
  struct GridData *ptr=NULL;
  ptr=malloc(sizeof(struct GridData));
  if (ptr==NULL) return 0;

  memset(ptr,0,sizeof(struct GridData));
  ptr->sdata=NULL;
  ptr->data=NULL;
  return ptr;
}

void GridFree(struct GridData *ptr) {
  if (ptr==NULL);
  if (ptr->sdata !=NULL) free(ptr->sdata);
  if (ptr->data !=NULL) free(ptr->data);
  free (ptr);
}

