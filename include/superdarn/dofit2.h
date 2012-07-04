/* dofit.h
   ========
   Author: R.J.Barnes
*/




#ifndef _DOFIT2_H
#define _DOFIT2_H

int do_fit2(struct FitBlock *iptr,int lag_lim,int goose,
	   struct FitRange *ptr,struct FitRange *xptr,
           struct FitElv *elv,
	   struct FitNoise *nptr,int print);

#endif
