/* sim.c
   ======== 
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <zlib.h>
#include "rtypes.h"
#include "dmap.h"
#include "simdata.h"

struct SimData *SimMake() {
  int n;
  struct SimData *ptr=NULL;
  ptr=malloc(sizeof(struct SimData));
  if (ptr==NULL) return NULL;
  memset(ptr,0,sizeof(struct SimData));
  ptr->pwr0=NULL;
  for (n=0;n<2;n++) {
    ptr->acfd[n]=NULL;
    ptr->xcfd[n]=NULL;
  }
  return ptr;
}

void SimFree(struct SimData *ptr) {
  int n;
  if (ptr==NULL) return;
  if (ptr->pwr0 !=NULL) free(ptr->pwr0);
  for (n=0;n<2;n++) {
    if (ptr->acfd[n] !=NULL) free(ptr->acfd[n]);
    if (ptr->xcfd[n] !=NULL) free(ptr->xcfd[n]);
  }
  free(ptr);
  return;
}

int SimSetPwr(struct SimData *ptr,int nrang,float *pwr0,int snum,int *slist) {
  void *tmp=NULL;
  int s;
  if (ptr==NULL) return -1;
  if ((nrang==0) || (pwr0==NULL)) {
    if (ptr->pwr0 !=NULL) free(ptr->pwr0);
    ptr->pwr0=NULL;
    return 0;
  }
  if (ptr->pwr0==NULL) tmp=malloc(sizeof(float)*nrang);
  else tmp=realloc(ptr->pwr0,sizeof(float)*nrang);

  if (tmp==NULL) return -1;
  ptr->pwr0=tmp;
  if (slist==NULL) memcpy(tmp,pwr0,sizeof(float)*nrang);
  else {
    memset(tmp,0,sizeof(float)*nrang);
    for (s=0;s<snum;s++) ptr->pwr0[slist[s]]=pwr0[s];
  }
  return 0;
}


int SimSetACF(struct SimData *ptr,int nrang,int mplgs,float *acfd,int snum,int *slist) {
  float *tmp=NULL;
  int n,x,y,s;
  if (ptr==NULL) return -1;
  if ((nrang*mplgs==0) || (acfd==NULL)) {
    for (n=0;n<2;n++) {
      if (ptr->acfd[n] !=NULL) free(ptr->acfd[n]);
      ptr->acfd[n]=NULL;
    }
    return 0;
  }

  for (n=0;n<2;n++) {
    if (ptr->acfd[n]==NULL) tmp=malloc(sizeof(float)*nrang*mplgs);
    else tmp=realloc(ptr->acfd[n],sizeof(float)*nrang*mplgs);
    if (tmp==NULL) return -1;
    ptr->acfd[n]=tmp;
    if (slist==NULL) {
      for (x=0;x<nrang;x++) {
        for (y=0;y<mplgs;y++) { 
          tmp[x*mplgs+y]=acfd[2*(x*mplgs+y)+n];
        }
      }
    } else {
      memset(tmp,0,sizeof(float)*nrang*mplgs);
      for (s=0;s<snum;s++) {
        x=slist[s];
        for (y=0;y<mplgs;y++) {
          tmp[x*mplgs+y]=acfd[2*(s*mplgs+y)+n];
        }
      }
    }
  }
  return 0;
}


int SimSetXCF(struct SimData *ptr,int nrang,int mplgs,float *xcfd,int snum,int *slist) {
  float *tmp=NULL;
  int n,x,y,s;
  if (ptr==NULL) return -1;
  if ((nrang*mplgs==0) || (xcfd==NULL)) {
    for (n=0;n<2;n++) {
      if (ptr->xcfd[n] !=NULL) free(ptr->xcfd[n]);
      ptr->xcfd[n]=NULL;
    }
    return 0;
  }

  for (n=0;n<2;n++) {
    if (ptr->xcfd[n]==NULL) tmp=malloc(sizeof(float)*nrang*mplgs);
    else tmp=realloc(ptr->xcfd[n],sizeof(float)*nrang*mplgs);
    if (tmp==NULL) return -1;
    ptr->xcfd[n]=tmp;
    if (slist==NULL) {
      for (x=0;x<nrang;x++) {
        for (y=0;y<mplgs;y++) {
          tmp[x*mplgs+y]=xcfd[2*(x*mplgs+y)+n];
        }
      }
    } else {
      memset(tmp,0,sizeof(float)*nrang*mplgs);
      for (s=0;s<snum;s++) {
        x=slist[s];
        for (y=0;y<mplgs;y++) {
          tmp[x*mplgs+y]=xcfd[2*(s*mplgs+y)+n];
        }
      }
    }
  }
  return 0;
}

