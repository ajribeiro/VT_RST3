/* math.c
   ======
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#include <stdlib.h>
#include <math.h>

double sgn(double a,double b) {
  double x=0;
  x=(double) (a>=0) ? a : -a;
  return (double) (b>=0) ? x: -x;
}

double mod(double x,double y) {
  double quotient;
  quotient = x / y;
  if (quotient >= 0) quotient = floor(quotient);
  else quotient = -floor(-quotient);
  return(x - y *quotient);
}





