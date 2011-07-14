/* tplot.h
   =======
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




struct tplot {
  int bmnum;
  int channel;
  int cpid;
  int scan;
  int nrang;
  int nave;
  struct {
    int sc;
    int us;
  } intt;
  int frang;
  int rsep;
  int rxrise;
  int noise;
  int tfreq;
  int atten;
  int *qflg;
  int *gsct;
  double *p_l;
  double *p_l_e;
  double *v;
  double *v_e;
  double *w_l;
  double *w_l_e;
}; 

int tplotset(struct tplot *ptr,int nrang);

