/* simwrite.c
   ========== 
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <zlib.h>
#include "rtypes.h"
#include "dmap.h"
#include "rprm.h"
#include "simdata.h"

int SimEncode(struct DataMap *ptr,struct RadarParm *prm,struct SimData *sim) {

  int tx;
  int c,d,x;
  int32 p0num,snum;
  int32 anum[3],xnum[3];
 
  int16 *slist=NULL;
  float *acfd=NULL;
  float *xcfd=NULL;

  DataMapAddScalar(ptr,"simacf.revision.major",DATAINT,
		    &sim->revision.major);

  DataMapAddScalar(ptr,"simacf.revision.minor",DATAINT,
		    &sim->revision.minor);

  DataMapAddScalar(ptr,"thr",DATAFLOAT,&sim->thr);
  DataMapAddScalar(ptr,"v_dop",DATAFLOAT,&sim->v_dop);
  DataMapAddScalar(ptr,"f_dop",DATAFLOAT,&sim->f_dop);
  DataMapAddScalar(ptr,"t_d",DATAFLOAT,&sim->t_d);
  DataMapAddScalar(ptr,"spec_width",DATAFLOAT,&sim->spec_width);
  DataMapAddScalar(ptr,"t_c",DATAFLOAT,&sim->t_c);
  DataMapAddScalar(ptr,"t_g",DATAFLOAT,&sim->t_g);
  DataMapAddScalar(ptr,"life_dist",DATAINT,&sim->life_dist);

  snum=0;
  tx=(int) ((sim->thr*prm->noise.search)/2.0);

  for (c=0;c<prm->nrang;c++) {
    if (sim->pwr0[c]<tx) continue;
    snum++;
  }

  p0num=prm->nrang;
  anum[0]=2;  
  anum[1]=prm->mplgs;
  anum[2]=snum;

  if (prm->xcf !=0) {
    xnum[0]=2;
    xnum[1]=prm->mplgs;
    xnum[2]=snum;
  } else {
    xnum[0]=0;
    xnum[1]=0;
    xnum[2]=0;
  }
  
  if (snum !=0) slist=DataMapStoreArray(ptr,"slist",DATASHORT,1,&snum,NULL);
  DataMapStoreArray(ptr,"pwr0",DATAFLOAT,1,&p0num,sim->pwr0);
  if (snum !=0) {
    acfd=DataMapStoreArray(ptr,"acfd",DATAFLOAT,3,anum,NULL);
    if (prm->xcf !=0) xcfd=DataMapStoreArray(ptr,"xcfd",DATAFLOAT,3,xnum,NULL);
    x=0;
    for (c=0;c<prm->nrang;c++) {
      if (sim->pwr0[c]<tx) continue;
      slist[x]=c;
      for (d=0;d<prm->mplgs;d++) {
        acfd[2*(x*prm->mplgs+d)]=sim->acfd[0][c*prm->mplgs+d];
        acfd[2*(x*prm->mplgs+d)+1]=sim->acfd[1][c*prm->mplgs+d];
      }
      if (prm->xcf !=0) for (d=0;d<prm->mplgs;d++) {
        xcfd[2*(x*prm->mplgs+d)]=sim->xcfd[0][c*prm->mplgs+d];
        xcfd[2*(x*prm->mplgs+d)+1]=sim->xcfd[1][c*prm->mplgs+d];
      }
      x++;
    }
  }
  return 0;
}


int SimWrite(int fid,struct RadarParm *prm,
            struct SimData *sim) {

  int s;
  struct DataMap *ptr=NULL;

  ptr=DataMapMake();
  if (ptr==NULL) return -1;

  s=RadarParmEncode(ptr,prm);

  if (s==0) s=SimEncode(ptr,prm,sim);

  if (s==0) {
    if (fid !=-1) s=DataMapWrite(fid,ptr);
    else s=DataMapSize(ptr);
  }

  DataMapFree(ptr);
  return s;

}

int SimFwrite(FILE *fp,struct RadarParm *prm,
              struct SimData *sim) {
  return SimWrite(fileno(fp),prm,sim);
}
