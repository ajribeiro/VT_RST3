/* reval.h
   ====== 
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef _REVAL_H
#define _REVAL_H

struct EvalStack {
  int num;
  unsigned char *buf;
};

struct EvalPostFix {
  int num;
  char *type;
  int  *object;

  int vnum;
  double *value;
};

int Eval(char *sum,double *ptr,
         int (*dvar)(char *ptr,double *val,void *data),
         void *vdata,
         int (*dfun)(char *ptr,int argnum,double *argptr,
                     double *val,void *data),
         void *fdata);

#endif
