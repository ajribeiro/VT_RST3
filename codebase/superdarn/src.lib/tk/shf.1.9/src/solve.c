/* solve.c
   ======= 
   Author:R.J.Barnes
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
#include "rmath.h"
#include "rfile.h"
#include "griddata.h"
#include "cnvmap.h"
#include "cnvgrid.h"
#include "solvepotential.h"
#include "solvevelocity.h"
#include "solveefield.h"



int CnvMapSolve(struct CnvMapData *ptr,struct CnvGrid *gptr) {
  if (gptr->type==0) return CnvMapSolvePotential(ptr,gptr);
  else if (gptr->type==2) return CnvMapSolveEfield(ptr,gptr);
  else return CnvMapSolveVelocity(ptr,gptr);
}

