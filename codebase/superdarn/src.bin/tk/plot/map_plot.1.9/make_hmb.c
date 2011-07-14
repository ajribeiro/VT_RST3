/* make_hmb.c
   ========== 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include "rtypes.h"
#include "rfile.h"
#include "griddata.h"
#include "cnvmap.h"
#include "polygon.h"




struct PolygonData *make_hmb(struct CnvMapData *map) {
  int i;
  float pnt[2];
  struct PolygonData *ptr;

  ptr=PolygonMake(sizeof(float)*2,NULL);
  PolygonAddPolygon(ptr,1);
           
  for (i=0;i<map->num_bnd;i++) {
    pnt[0]=map->bnd_lat[i];
    pnt[1]=map->bnd_lon[i];
    PolygonAdd(ptr,pnt);
  }
  return ptr;
}




