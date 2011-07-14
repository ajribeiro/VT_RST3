/* math.h
   ======
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef PI
#define PI 3.14159265358979323846
#endif

#define cosd(a) cos(PI*(a)/180)
#define sind(a) sin(PI*(a)/180)
 
#define scosd(a) (acos(a)*180/PI)
#define asind(a) (asin(a)*180/PI)

double sgn(double,double);
double mod(double,double);
