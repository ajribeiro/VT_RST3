/* dihf.c
   ======
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#include <math.h>
#include "rmath.h"

int dihf(float x, float y, float z, float *d, float *i, 
          float *h, float *f) {
   
    float h2;
    float sn, hpx;

    sn = (float)1e-4;

    h2 = x * x + y * y;
    *h = sqrt(h2);
    *f = sqrt(h2 + z * z);
    if (*f < sn) {
	*d = (float)999.;
	*i = (float)999.;
    } else {
	*i = atan2d(z,*h);

	if (*h < sn) {
	    *d = (float)999.;
	} else {
	    hpx = *h + x;
	    if (hpx < sn) {
		*d = (float) 180.;
	    } else {
		*d = atan2d(y,hpx) * (float)2.;
	    }
	}
    }
    return 0;
} 


