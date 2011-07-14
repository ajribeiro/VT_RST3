/* magcmp.c
   ========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#include <math.h>
#include <stdio.h>
#include "igrfcall.h"



int IGRFMagCmp(double date, double frho, double flat, double flon, 
           double *bx, double *by, double *bz, double *b) {

    frho = frho - 6372.;
    IGRFCall(date, flat, flon, frho, bx, by, bz);
    *b = sqrt(*bx * *bx + *by * *by + *bz * *bz);
    *bx = -*bx;
    *bz = -*bz;
    return 0;
} 

