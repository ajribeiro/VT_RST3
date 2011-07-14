/* cfit.h
   ======
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




double cfit_find(struct CFitfp *cfitfp,struct CFitdata *fit,double sdate,
                double stime);
 
double cfit_scan(double ctime,struct CFitfp *cfitfp,int rflg,
                struct CFitdata *fit,
                int bmnum,int chnum,int cpid,int sflg,int scan);

void cfit_tplot(struct CFitdata *fit,struct tplot *tptr);
 
