/* time.c
   ======
   Author: R.J.Barnes
*/

/*
 Copyright 2004 The Johns Hopkins University/Applied Physics Laboratory.
 All rights reserved.

 This material may be used, modified, or reproduced by or for the U.S.
 Government pursuant to the license rights granted under the clauses at DFARS
 252.227-7013/7014.

 For any other permissions, please contact the Space Department
 Program Office at JHU/APL.

 This Distribution and Disclaimer Statement must be included in all copies of
 "Radar Software Toolkit - SuperDARN Toolkit" (hereinafter "the Program").

 The Program was developed at The Johns Hopkins University/Applied Physics
 Laboratory (JHU/APL) which is the author thereof under the "work made for
 hire" provisions of the copyright law.

 JHU/APL assumes no obligation to provide support of any kind with regard to
 the Program.  This includes no obligation to provide assistance in using the
 Program or to provide updated versions of the Program.

 THE PROGRAM AND ITS DOCUMENTATION ARE PROVIDED AS IS AND WITHOUT ANY EXPRESS
 OR IMPLIED WARRANTIES WHATSOEVER.  ALL WARRANTIES INCLUDING, BUT NOT LIMITED
 TO, PERFORMANCE, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE ARE
 HEREBY DISCLAIMED.  YOU ASSUME THE ENTIRE RISK AND LIABILITY OF USING THE
 PROGRAM TO INCLUDE USE IN COMPLIANCE WITH ANY THIRD PARTY RIGHTS.  YOU ARE
 ADVISED TO TEST THE PROGRAM THOROUGHLY BEFORE RELYING ON IT.  IN NO EVENT
 SHALL JHU/APL BE LIABLE FOR ANY DAMAGES WHATSOEVER, INCLUDING, WITHOUT
 LIMITATION, ANY LOST PROFITS, LOST SAVINGS OR OTHER INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, ARISING OUT OF THE USE OR INABILITY TO USE THE
 PROGRAM."






*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <math.h>
#include <time.h>
#include "rtime.h"

/*
 $Log: time.c,v $
 Revision 1.2  2004/04/26 21:16:32  barnes
 Audit - Enforced warning set to "all".

 Revision 1.1  2004/04/17 19:53:22  barnes
 Initial revision

*/

#define DAY_SEC (24.0*3600.0)
#define YEAR_SEC (365.0*24*3600.0)
#define LYEAR_SEC (366.0*24.0*3600.0)

void TimeYrsecToYMDHMS(int time,int yr,
              int *mo,int *dy,
              int *hr,int *mn,int *sc) {
  int yd;
  int dt;
  int n;
  int *jday;

  int nday[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
  int lday[12] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};

  if (((yr % 4)==0) && (((yr % 100) !=0) || ((yr % 400)==0))) jday=lday;
  else jday=nday;

  yd=time/(24L*60L*60L); /* get the day of the year */

  for (n=0;(n<12) && (yd>=jday[n]);n++);

  *mo=n; /* got the month */
  if (n>0) *dy=1+yd-jday[n-1]; /* got the date */
   else *dy=yd+1;

  dt=time % (24L*60L*60L);
  *hr=dt/(60L*60L);
  *mn=(dt % (60L*60L))/60L;
  *sc=dt % 60L;
}

int TimeYMDHMSToYrsec(int yr, int mo, int day, int hr, int mn,int sec) {
  int t;
  int jday[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
  int mday[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if ( (mo < 1) || (mo > 12) || (hr < 0) || (hr > 23) ||
       (day <1) || (mn < 0) || (mn > 59) || (sec < 0) || (sec >= 60) )
	   return -1;

  if (day > mday[mo-1]) {
	if (mo != 2) return -1;
	else if (day != (mday[1] +1) || ((yr % 4) != 0)) return -1;
  }
  t = jday[mo-1] + day - 1;

  if ( (mo > 2) && ((yr % 4) == 0) &&
       (((yr % 100) !=0) || ((yr % 400)==0))) t = t+1;

  return (((t*24L + hr)*60L + mn)*60L)+sec;
}

double TimeYMDHMSToEpoch(int yr,int mo,int dy,int hr,int mn,double sec) {
   double tme;
   int lpyear,ryear;
   int yrsec;
   if (yr<1970) return -1;
   yrsec=TimeYMDHMSToYrsec(yr,mo,dy,hr,mn,(int) sec);
   if (yrsec==-1) return -1;
   tme=yrsec+(sec-(int) sec);

   /* work out number of seconds from 1970 to start of year */

   lpyear=(yr-1969)/4;
   ryear=(yr-1970)-lpyear;

   tme+=(lpyear*LYEAR_SEC)+(ryear*YEAR_SEC);
   return tme;
}

void TimeEpochToYMDHMS(double tme,int *yr,int *mo,int *dy,int *hr,int *mn,
	       double *sc) {
  int yrsec=0;
  int sec;
  int i=0;

  /* find the year */

  while ((yrsec<=tme) && (i<1e6)) {
    if ((i % 4)==2) yrsec+=LYEAR_SEC;
    else yrsec+=YEAR_SEC;
    i++;
  }
  if (((i-1) % 4)==2) tme-=yrsec-LYEAR_SEC;
  else tme-=yrsec-YEAR_SEC;
  *yr=i+1969;
  TimeYrsecToYMDHMS( (int) tme,*yr,mo,dy,hr,mn,&sec);

  *sc=sec+(tme-(int) tme);

}


double TimeYMDHMSToJulian(int yr,int mo,int dy,int hr,int mt,double sc) {

  int A,B,i;
  double jdoy;
  double dfrac;
  yr=yr-1;
  i=yr/100;
  A=i;
  i=A/4;
  B=2-A+i;
  i=365.25*yr;
  i+=30.6001*14;
  jdoy=i+1720994.5+B;


  dfrac=1+TimeYMDHMSToYrsec(yr+1,mo,dy,hr,mt,sc)/DAY_SEC;

  return jdoy+dfrac;

}


int TimeJulianToYMDHMS(double jd,int *yr,int *mo,
                 int *dy,int *hr,int *mt,double *sc) {

  int Z,month;
  int hour,minute;

  double A,B,C,D,E,F,alpha,day,year,factor,second;

  factor=0.5/DAY_SEC/1000;
  F=(jd+0.5)-floor(jd+0.5);
  if ((F+factor)>=1.0) {
    jd=jd+factor;
    F=0.0;
  }

  Z=floor(jd+0.5);

  if (Z<2299161) A=Z;
  else {
    alpha=floor((Z-1867216.25)/36524.25);
    A=Z+1+alpha-floor(alpha/4);
  }

  B=A+1524;
  C=floor((B-122.1)/365.25);
  D=floor(365.25*C);
  E=floor((B-D)/30.6001);
  day=B-D-floor(30.6001*E)+F;

  if (E<13.5) month=floor(E-0.5);
  else month=floor(E-12.5);
  if (month>2.5) year=C-4716;
  else year=C-4715;



  *yr=(int) year;
  *mo=month;
  *dy=(int) floor(day);

  /* okay now use the residual of the day to work out the time */

  A=(day-floor(day))*DAY_SEC;

  hour=(int) (A/3600.0);
  minute=(int) ((A-hour*3600)/60);
  second=A-hour*3600-minute*60;

  *hr=hour;
  *mt=minute;
  *sc=second;
  return 0;
}

