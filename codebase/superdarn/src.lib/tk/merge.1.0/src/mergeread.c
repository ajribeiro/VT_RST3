/* radar.c
   =======
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
#include "mergedata.h"
#include "mergeread.h"



int MergeDecode(struct DataMap *ptr,struct MergeData *data)
{

  int c;
  struct DataMapScalar *s;

  if (ptr==NULL) return -1;
  if (data==NULL) return -1;

  memset(data,0,sizeof(struct MergeData));

  for (c=0;c<ptr->snum;c++)
	{
    s=ptr->scl[c];
<<<<<<< HEAD

    if ((strcmp(s->name,"radar1.stid")==0) && (s->type==DATASHORT))
      data->radar1.stid=*(s->data.sptr);
=======
		fprintf(stderr,"%d  %s  %d  %f\n",ptr->snum,s->name,s->type,(float)(*s->data.fptr));

    if ((strcmp(s->name,"radar1.stid")==0) && (s->type==DATASHORT))
      data->radar1.stid=*(s->data.iptr);
>>>>>>> fitcomp
		if ((strcmp(s->name,"radar1.qflg")==0) && (s->type==DATASHORT))
      data->radar1.qflg=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.cpid")==0) && (s->type==DATASHORT))
      data->radar1.cpid=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.beam")==0) && (s->type==DATASHORT))
      data->radar1.beam=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.rng")==0) && (s->type==DATASHORT))
      data->radar1.rng=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.gsflg")==0) && (s->type==DATASHORT))
<<<<<<< HEAD
      data->radar1.gsflg=*(s->data.fptr);
		if ((strcmp(s->name,"radar1.vel")==0) && (s->type==DATAFLOAT))
      data->radar1.vel=*(s->data.fptr);
		if ((strcmp(s->name,"radar1.vel_err")==0) && (s->type==DATAFLOAT))
      data->radar1.vel_err=*(s->data.fptr);
		if ((strcmp(s->name,"radar1.pwr")==0) && (s->type==DATAFLOAT))
      data->radar1.pwr=*(s->data.fptr);
		if ((strcmp(s->name,"radar1.w_l")==0) && (s->type==DATAFLOAT))
      data->radar1.w_l=*(s->data.fptr);
		if ((strcmp(s->name,"radar1.glat")==0) && (s->type==DATAFLOAT))
      data->radar1.glat=*(s->data.fptr);
		if ((strcmp(s->name,"radar1.glon")==0) && (s->type==DATAFLOAT))
      data->radar1.glon=*(s->data.fptr);
		if ((strcmp(s->name,"radar1.gazm")==0) && (s->type==DATAFLOAT))
      data->radar1.gazm=*(s->data.fptr);
		if ((strcmp(s->name,"radar1.mlat")==0) && (s->type==DATAFLOAT))
      data->radar1.mlat=*(s->data.fptr);
		if ((strcmp(s->name,"radar1.mlon")==0) && (s->type==DATAFLOAT))
      data->radar1.mlon=*(s->data.fptr);
		if ((strcmp(s->name,"radar1.mazm")==0) && (s->type==DATAFLOAT))
      data->radar1.mazm=*(s->data.fptr);
		if ((strcmp(s->name,"radar1.st_time")==0) && (s->type==DATAINT))
      data->radar1.st_time=*(s->data.iptr);
		if ((strcmp(s->name,"radar1.ed_time")==0) && (s->type==DATAINT))
      data->radar1.ed_time=*(s->data.iptr);
=======
      data->radar1.gsflg=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.vel")==0) && (s->type==DATAFLOAT))
      data->radar1.vel=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.vel_err")==0) && (s->type==DATAFLOAT))
      data->radar1.vel_err=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.pwr")==0) && (s->type==DATAFLOAT))
      data->radar1.pwr=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.w_l")==0) && (s->type==DATAFLOAT))
      data->radar1.w_l=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.glat")==0) && (s->type==DATAFLOAT))
      data->radar1.glat=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.glon")==0) && (s->type==DATAFLOAT))
      data->radar1.glon=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.gazm")==0) && (s->type==DATAFLOAT))
      data->radar1.gazm=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.mlat")==0) && (s->type==DATAFLOAT))
      data->radar1.mlat=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.mlon")==0) && (s->type==DATAFLOAT))
      data->radar1.mlon=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.mazm")==0) && (s->type==DATAFLOAT))
      data->radar1.mazm=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.st_time")==0) && (s->type==DATAINT))
      data->radar1.st_time=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.ed_time")==0) && (s->type==DATAINT))
      data->radar1.ed_time=*(s->data.sptr);
>>>>>>> fitcomp


		if ((strcmp(s->name,"radar2.stid")==0) && (s->type==DATASHORT))
      data->radar2.stid=*(s->data.sptr);
		if ((strcmp(s->name,"radar2.qflg")==0) && (s->type==DATASHORT))
      data->radar2.qflg=*(s->data.sptr);
		if ((strcmp(s->name,"radar2.cpid")==0) && (s->type==DATASHORT))
      data->radar2.cpid=*(s->data.sptr);
		if ((strcmp(s->name,"radar2.beam")==0) && (s->type==DATASHORT))
      data->radar2.beam=*(s->data.sptr);
		if ((strcmp(s->name,"radar2.rng")==0) && (s->type==DATASHORT))
      data->radar2.rng=*(s->data.sptr);
		if ((strcmp(s->name,"radar2.gsflg")==0) && (s->type==DATASHORT))
<<<<<<< HEAD
      data->radar2.gsflg=*(s->data.fptr);
		if ((strcmp(s->name,"radar2.vel")==0) && (s->type==DATAFLOAT))
      data->radar2.vel=*(s->data.fptr);
		if ((strcmp(s->name,"radar2.vel_err")==0) && (s->type==DATAFLOAT))
      data->radar2.vel_err=*(s->data.fptr);
		if ((strcmp(s->name,"radar2.pwr")==0) && (s->type==DATAFLOAT))
      data->radar2.pwr=*(s->data.fptr);
		if ((strcmp(s->name,"radar2.w_l")==0) && (s->type==DATAFLOAT))
      data->radar2.w_l=*(s->data.fptr);
		if ((strcmp(s->name,"radar2.glat")==0) && (s->type==DATAFLOAT))
      data->radar2.glat=*(s->data.fptr);
		if ((strcmp(s->name,"radar2.glon")==0) && (s->type==DATAFLOAT))
      data->radar2.glon=*(s->data.fptr);
		if ((strcmp(s->name,"radar2.gazm")==0) && (s->type==DATAFLOAT))
      data->radar2.gazm=*(s->data.fptr);
		if ((strcmp(s->name,"radar2.mlat")==0) && (s->type==DATAFLOAT))
      data->radar2.mlat=*(s->data.fptr);
		if ((strcmp(s->name,"radar2.mlon")==0) && (s->type==DATAFLOAT))
      data->radar2.mlon=*(s->data.fptr);
		if ((strcmp(s->name,"radar2.mazm")==0) && (s->type==DATAFLOAT))
      data->radar2.mazm=*(s->data.fptr);
		if ((strcmp(s->name,"radar2.st_time")==0) && (s->type==DATAINT))
      data->radar2.st_time=*(s->data.iptr);
		if ((strcmp(s->name,"radar2.ed_time")==0) && (s->type==DATAINT))
      data->radar2.ed_time=*(s->data.iptr);

		if ((strcmp(s->name,"velg")==0) && (s->type==DATAFLOAT))
      data->velg=*(s->data.fptr);
		if ((strcmp(s->name,"velm")==0) && (s->type==DATAFLOAT))
      data->velm=*(s->data.fptr);
		if ((strcmp(s->name,"glat")==0) && (s->type==DATAFLOAT))
      data->glat=*(s->data.fptr);
		if ((strcmp(s->name,"glon")==0) && (s->type==DATAFLOAT))
      data->glon=*(s->data.fptr);
		if ((strcmp(s->name,"gazm")==0) && (s->type==DATAFLOAT))
      data->gazm=*(s->data.fptr);
		if ((strcmp(s->name,"mlat")==0) && (s->type==DATAFLOAT))
      data->mlat=*(s->data.fptr);
		if ((strcmp(s->name,"mlon")==0) && (s->type==DATAFLOAT))
      data->mlon=*(s->data.fptr);
		if ((strcmp(s->name,"mazm")==0) && (s->type==DATAFLOAT))
      data->mazm=*(s->data.fptr);
		if ((strcmp(s->name,"dgeo")==0) && (s->type==DATAFLOAT))
      data->dgeo=*(s->data.fptr);
		if ((strcmp(s->name,"dmag")==0) && (s->type==DATAFLOAT))
      data->dmag=*(s->data.fptr);
		if ((strcmp(s->name,"st_time")==0) && (s->type==DATAINT))
      data->st_time=*(s->data.iptr);
		if ((strcmp(s->name,"ed_time")==0) && (s->type==DATAINT))
      data->ed_time=*(s->data.iptr);
=======
      data->radar2.gsflg=*(s->data.sptr);
		if ((strcmp(s->name,"radar2.vel")==0) && (s->type==DATAFLOAT))
      data->radar2.vel=*(s->data.sptr);
		if ((strcmp(s->name,"radar2.vel_err")==0) && (s->type==DATAFLOAT))
      data->radar2.vel_err=*(s->data.sptr);
		if ((strcmp(s->name,"radar2.pwr")==0) && (s->type==DATAFLOAT))
      data->radar2.pwr=*(s->data.sptr);
		if ((strcmp(s->name,"radar2.w_l")==0) && (s->type==DATAFLOAT))
      data->radar2.w_l=*(s->data.sptr);
		if ((strcmp(s->name,"radar2.glat")==0) && (s->type==DATAFLOAT))
      data->radar2.glat=*(s->data.sptr);
		if ((strcmp(s->name,"radar2.glon")==0) && (s->type==DATAFLOAT))
      data->radar2.glon=*(s->data.sptr);
		if ((strcmp(s->name,"radar2.gazm")==0) && (s->type==DATAFLOAT))
      data->radar2.gazm=*(s->data.sptr);
		if ((strcmp(s->name,"radar2.mlat")==0) && (s->type==DATAFLOAT))
      data->radar2.mlat=*(s->data.sptr);
		if ((strcmp(s->name,"radar2.mlon")==0) && (s->type==DATAFLOAT))
      data->radar2.mlon=*(s->data.sptr);
		if ((strcmp(s->name,"radar2.mazm")==0) && (s->type==DATAFLOAT))
      data->radar2.mazm=*(s->data.sptr);
		if ((strcmp(s->name,"radar2.st_time")==0) && (s->type==DATAINT))
      data->radar2.st_time=*(s->data.sptr);
		if ((strcmp(s->name,"radar2.ed_time")==0) && (s->type==DATAINT))
      data->radar2.ed_time=*(s->data.sptr);

		if ((strcmp(s->name,"velg")==0) && (s->type==DATAFLOAT))
      data->velg=*(s->data.sptr);
		if ((strcmp(s->name,"velm")==0) && (s->type==DATAFLOAT))
      data->velm=*(s->data.sptr);
		if ((strcmp(s->name,"glat")==0) && (s->type==DATAFLOAT))
      data->glat=*(s->data.sptr);
		if ((strcmp(s->name,"glon")==0) && (s->type==DATAFLOAT))
      data->glon=*(s->data.sptr);
		if ((strcmp(s->name,"gazm")==0) && (s->type==DATAFLOAT))
      data->gazm=*(s->data.sptr);
		if ((strcmp(s->name,"mlat")==0) && (s->type==DATAFLOAT))
      data->mlat=*(s->data.sptr);
		if ((strcmp(s->name,"mlon")==0) && (s->type==DATAFLOAT))
      data->mlon=*(s->data.sptr);
		if ((strcmp(s->name,"mazm")==0) && (s->type==DATAFLOAT))
      data->mazm=*(s->data.sptr);
		if ((strcmp(s->name,"dgeo")==0) && (s->type==DATAFLOAT))
      data->dgeo=*(s->data.sptr);
		if ((strcmp(s->name,"dmag")==0) && (s->type==DATAFLOAT))
      data->dmag=*(s->data.sptr);
		if ((strcmp(s->name,"st_time")==0) && (s->type==DATAINT))
      data->st_time=*(s->data.sptr);
		if ((strcmp(s->name,"ed_time")==0) && (s->type==DATAINT))
      data->ed_time=*(s->data.sptr);
>>>>>>> fitcomp

  }

  return 0;
}

int MergeRead(int fid,struct MergeData *data)
{

  int s;
  struct DataMap *ptr;

  ptr=DataMapRead(fid);
  if (ptr==NULL) return -1;
  s=MergeDecode(ptr,data);
	if (s !=0)
	{
    DataMapFree(ptr);
    return s;
  }
  s=MergeDecode(ptr,data);
  DataMapFree(ptr);
  return s;
}

int MergeFread(FILE *fp,struct MergeData *data)
{
  return MergeRead(fileno(fp),data);
}



