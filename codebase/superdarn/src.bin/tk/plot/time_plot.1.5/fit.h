/* fit.h
   =====
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




double fit_find(FILE *fp,struct RadarParm *prm,
                struct FitData *fit,double sdate,
                double stime,struct FitIndex *inx);
 
double fit_scan(double ctime,FILE *fp,int rflg,
                struct RadarParm *prm,struct FitData *fit,
                int bmnum,int chnum,int cpid,int sflg,int scan);

void fit_tplot(struct RadarParm *prm,struct FitData *fit,struct tplot *tptr);
 
