/* simread.c
   ========= 
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
#include <zlib.h>
#include "rtypes.h"
#include "dmap.h"
#include "rprm.h"
#include "simdata.h"


int SimDecode(struct DataMap *ptr,struct SimData *sim) {

  int c,n;
 
  int *slist=NULL;
  struct DataMapScalar *s;
  struct DataMapArray *a;
  int snum=0,nrang=0;
  

  if (sim->pwr0 !=NULL) free(sim->pwr0);
  for (n=0;n<2;n++) { 
    if (sim->acfd[n] !=NULL) free(sim->acfd[n]);
    if (sim->xcfd[n] !=NULL) free(sim->xcfd[n]);
  }
  memset(sim,0,sizeof(struct SimData));
  sim->pwr0=NULL;
  for (n=0;n<2;n++) {
    sim->acfd[n]=NULL;
    sim->xcfd[n]=NULL;
  }

  for (c=0;c<ptr->snum;c++) {
    s=ptr->scl[c];
   
    if ((strcmp(s->name,"simacf.revision.major")==0) && (s->type==DATAINT))
      sim->revision.major=*(s->data.iptr);
    if ((strcmp(s->name,"simacf.revision.minor")==0) && (s->type==DATAINT))
      sim->revision.minor=*(s->data.iptr);

    if ((strcmp(s->name,"thr")==0) && (s->type==DATAFLOAT))
      sim->thr=*(s->data.fptr);
    if ((strcmp(s->name,"v_dop")==0) && (s->type==DATAFLOAT))
      sim->v_dop=*(s->data.fptr);
    if ((strcmp(s->name,"f_dop")==0) && (s->type==DATAFLOAT))
      sim->f_dop=*(s->data.fptr);
    if ((strcmp(s->name,"t_d")==0) && (s->type==DATAFLOAT))
      sim->t_d=*(s->data.fptr);
    if ((strcmp(s->name,"spec_width")==0) && (s->type==DATAFLOAT))
      sim->spec_width=*(s->data.fptr);
    if ((strcmp(s->name,"t_g")==0) && (s->type==DATAFLOAT))
      sim->t_g=*(s->data.fptr);
    if ((strcmp(s->name,"t_c")==0) && (s->type==DATAFLOAT))
      sim->t_c=*(s->data.fptr);
  }
 
  for (c=0;c<ptr->anum;c++) {
    a=ptr->arr[c];
  
    if ((strcmp(a->name,"slist")==0) && (a->type==DATASHORT) &&
        (a->dim==1)) {
      snum=a->rng[0];
      slist=malloc(sizeof(int)*snum);
      if (slist==NULL) break;
      for (n=0;n<snum;n++) slist[n]=a->data.sptr[n];
    }


    if ((strcmp(a->name,"pwr0")==0) && (a->type==DATAFLOAT) &&
        (a->dim==1)) {
      nrang=a->rng[0];
      SimSetPwr(sim,nrang,a->data.fptr,0,NULL);
    }
  }

  if ((snum==0) || (slist==NULL)) return 0;

  for (c=0;c<ptr->anum;c++) {
    a=ptr->arr[c];
    if ((strcmp(a->name,"acfd")==0) && (a->type==DATAFLOAT) &&
	(a->dim==3)) 
      SimSetACF(sim,nrang,a->rng[1],a->data.fptr,snum,slist);
 
    if ((strcmp(a->name,"xcfd")==0) && (a->type==DATAFLOAT) &&
	(a->dim==3)) 
      SimSetXCF(sim,nrang,a->rng[1],a->data.fptr,snum,slist);
  }
  free(slist);
  return 0;

}


int SimRead(int fid,struct RadarParm *prm,struct SimData *sim) {

  int s;
  struct DataMap *ptr;

  ptr=DataMapRead(fid);
  if (ptr==NULL) return -1;
  s=RadarParmDecode(ptr,prm);
  if (s !=0) {
    DataMapFree(ptr);
    return s;
  }
  s=SimDecode(ptr,sim);
  DataMapFree(ptr);
  return s;
}

int SimFread(FILE *fp,struct RadarParm *prm,
              struct SimData *sim) {
  return SimRead(fileno(fp),prm,sim);
}
