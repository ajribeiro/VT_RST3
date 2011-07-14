/* sza.c
   =====
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include "rmath.h"
#include "AstAlg.h"

double SZASolarDec(int yr,int mo,int dy,int hr,int mt,int sc) {

  double jd;
  double dd;
  
  dd=AstAlg_dday(dy-1,hr,mt,sc);
  jd=AstAlg_jde(yr,mo,dd);
  
  return AstAlg_solar_declination(jd); 
}

double SZAEqOfTime(int yr,int mo,int dy,int hr,int mt,int sc) {

  double jd;
  double dd;
  double eqt;

  dd=AstAlg_dday(dy-1,hr,mt,sc);
  jd=AstAlg_jde(yr,mo,dd);

  eqt=AstAlg_equation_of_time(jd);
  return eqt*60.0;
}


double SZAAngle(double lon,double lat,double dec,double Hangle) {
  double Z;
  Z=acos(sin(PI*lat/180.0)*sin(PI*dec/180.0)+
         cos(PI*lat/180.0)*cos(PI*dec/180.0)*cos(PI*Hangle/180.0))*180.0/PI;
  return Z;
}







