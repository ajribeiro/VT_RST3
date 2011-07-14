/* cnvgrid.h
   =========  
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef _CNVGRID_H
#define _CNVGRID_H

#define GRIDPOTENTIAL 0
#define GRIDVELOCITY 1

struct CnvGrid {
  int type;
  int num;
  int nlat;
  int nlon;
  int poly;
  int *vertex;
  double *lat;
  double *lon;
  double *mag;
  double *azm;
  double *ex;
  double *ey;
};

struct CnvGrid *CnvGridMake();
void CnvGridFree(struct CnvGrid *ptr);

#endif








