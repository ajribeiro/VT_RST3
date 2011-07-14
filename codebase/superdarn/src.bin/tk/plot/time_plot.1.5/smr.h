/* smr.h
   =====
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



double smr_find(FILE *fp,struct RadarParm *prm,
                struct FitData *fit,int fbeam,double sdate,
                double stime);
  
double smr_scan(double ctime,FILE *fp,int fbeam,int rflg,
                struct RadarParm *prm,
                struct FitData *fit,
                int bmnum,int chnum,int cpid,int sflg,int scan);

