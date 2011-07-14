/* tplot.c
   =======
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include "tplot.h"



int tplotset(struct tplot *ptr,int nrang) {
  void *tmp=NULL;
  if (ptr==NULL) return -1;
    
  if (ptr->qflg==NULL) tmp=malloc(sizeof(int)*nrang);
  else tmp=realloc(ptr->qflg,sizeof(int)*nrang);
  if (tmp==NULL) return -1;
  memset(tmp,0,sizeof(int)*nrang);
  ptr->qflg=tmp;

  if (ptr->gsct==NULL) tmp=malloc(sizeof(int)*nrang);
  else tmp=realloc(ptr->gsct,sizeof(int)*nrang);
  if (tmp==NULL) return -1;
  memset(tmp,0,sizeof(int)*nrang);
  ptr->gsct=tmp;


  if (ptr->p_l==NULL) tmp=malloc(sizeof(double)*nrang);
  else tmp=realloc(ptr->p_l,sizeof(double)*nrang);
  if (tmp==NULL) return -1;
  memset(tmp,0,sizeof(double)*nrang);
  ptr->p_l=tmp;

  if (ptr->p_l_e==NULL) tmp=malloc(sizeof(double)*nrang);
  else tmp=realloc(ptr->p_l_e,sizeof(double)*nrang);
  if (tmp==NULL) return -1;
  memset(tmp,0,sizeof(double)*nrang);
  ptr->p_l_e=tmp;

  if (ptr->v==NULL) tmp=malloc(sizeof(double)*nrang);
  else tmp=realloc(ptr->v,sizeof(double)*nrang);
  if (tmp==NULL) return -1;
  memset(tmp,0,sizeof(double)*nrang);
  ptr->v=tmp;


  if (ptr->v_e==NULL) tmp=malloc(sizeof(double)*nrang);
  else tmp=realloc(ptr->v_e,sizeof(double)*nrang);
  if (tmp==NULL) return -1;
  memset(tmp,0,sizeof(double)*nrang);
  ptr->v_e=tmp;


  if (ptr->w_l==NULL) tmp=malloc(sizeof(double)*nrang);
  else tmp=realloc(ptr->w_l,sizeof(double)*nrang);
  if (tmp==NULL) return -1;
  memset(tmp,0,sizeof(double)*nrang);
  ptr->w_l=tmp;


  if (ptr->w_l_e==NULL) tmp=malloc(sizeof(double)*nrang);
  else tmp=realloc(ptr->w_l_e,sizeof(double)*nrang);
  if (tmp==NULL) return -1;
  memset(tmp,0,sizeof(double)*nrang);
  ptr->w_l_e=tmp;
  return 0;

}
