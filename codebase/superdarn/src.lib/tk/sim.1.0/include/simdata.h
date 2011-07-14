/* simdata.h
   ========== 

  Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#ifndef _SIMDATA_H
#define _SIMDATA_H

struct SimData {
  struct {
    int major;
    int minor;
  } revision;
  float thr;
  float *pwr0;      /*lag 0 powers*/
  float *acfd[2];   /*ACFs*/
  float *xcfd[2];   /*XCFs*/
  float v_dop;      /*simulated Doppler velocity*/
  float f_dop;      /*simulated Doppler frequency*/
  float t_d;        /*simulated decay time*/
  float spec_width; /*simulated spectral width*/
  float t_g;        /*simulated growth time*/
  float t_c;        /*simulated lifetime cutoff*/
  int life_dist;    /*lifetime distribution (0=exponential, 1=constant)*/
};


struct SimData *SimMake();
void SimFree(struct SimData *ptr);
int SimSetPwr(struct SimData *ptr,int nrang,float *pwr0,int snum,int *slist);
int SimSetACF(struct SimData *ptr,int nrang,int mplgs,float *acfd,int snum,int *slist);
int SimSetXCF(struct SimData *ptr,int nrang,int mplgs,float *xcfd,int snum,int *slist);





#endif
