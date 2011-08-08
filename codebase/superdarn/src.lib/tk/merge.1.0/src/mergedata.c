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
#include <zlib.h>
#include "rtypes.h"
#include "dmap.h"
#include "mergedata.h"





int MergeDecode(struct DataMap *ptr,struct MergeData *data) {

  int c;
  struct DataMapScalar *s;

  if (ptr==NULL) return -1;
  if (data==NULL) return -1;

  memset(data,0,sizeof(struct MergeData));

  for (c=0;c<ptr->snum;c++)
	{
    s=ptr->scl[c];

    if ((strcmp(s->name,"radar1.stid")==0) && (s->type==DATASHORT))
      data->radar1.stid=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.qflg")==0) && (s->type==DATASHORT))
      data->radar1.qflg=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.cpid")==0) && (s->type==DATASHORT))
      data->radar1.cpid=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.beam")==0) && (s->type==DATASHORT))
      data->radar1.beam=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.rng")==0) && (s->type==DATASHORT))
      data->radar1.rng=*(s->data.sptr);
		if ((strcmp(s->name,"radar1.gsflg")==0) && (s->type==DATASHORT))
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

  }

  return 0;
}

int MergeEncode(struct DataMap *ptr,struct MergeData *data)
{


  DataMapAddScalar(ptr,"radar1.stid",DATASHORT,&data->radar1.stid);
	DataMapAddScalar(ptr,"radar1.qflg",DATASHORT,&data->radar1.qflg);
	DataMapAddScalar(ptr,"radar1.cpid",DATASHORT,&data->radar1.cpid);
	DataMapAddScalar(ptr,"radar1.beam",DATASHORT,&data->radar1.beam);
	DataMapAddScalar(ptr,"radar1.rng",DATASHORT,&data->radar1.rng);
	DataMapAddScalar(ptr,"radar1.gsflg",DATASHORT,&data->radar1.gsflg);
	DataMapAddScalar(ptr,"radar1.vel",DATAFLOAT,&data->radar1.vel);
	DataMapAddScalar(ptr,"radar1.vel_err",DATAFLOAT,&data->radar1.vel_err);
	DataMapAddScalar(ptr,"radar1.pwr",DATAFLOAT,&data->radar1.pwr);
	DataMapAddScalar(ptr,"radar1.w_l",DATAFLOAT,&data->radar1.w_l);
	DataMapAddScalar(ptr,"radar1.glat",DATAFLOAT,&data->radar1.glat);
	DataMapAddScalar(ptr,"radar1.glon",DATAFLOAT,&data->radar1.glon);
	DataMapAddScalar(ptr,"radar1.gazm",DATAFLOAT,&data->radar1.gazm);
	DataMapAddScalar(ptr,"radar1.mlat",DATAFLOAT,&data->radar1.mlat);
	DataMapAddScalar(ptr,"radar1.mlon",DATAFLOAT,&data->radar1.mlon);
	DataMapAddScalar(ptr,"radar1.mazm",DATAFLOAT,&data->radar1.mazm);
	DataMapAddScalar(ptr,"radar1.st_time",DATAINT,&data->radar1.st_time);
	DataMapAddScalar(ptr,"radar1.ed_time",DATAINT,&data->radar1.ed_time);

	DataMapAddScalar(ptr,"radar2.stid",DATASHORT,&data->radar2.stid);
	DataMapAddScalar(ptr,"radar2.qflg",DATASHORT,&data->radar2.qflg);
	DataMapAddScalar(ptr,"radar2.cpid",DATASHORT,&data->radar2.cpid);
	DataMapAddScalar(ptr,"radar2.beam",DATASHORT,&data->radar2.beam);
	DataMapAddScalar(ptr,"radar2.rng",DATASHORT,&data->radar2.rng);
	DataMapAddScalar(ptr,"radar2.gsflg",DATASHORT,&data->radar2.gsflg);
	DataMapAddScalar(ptr,"radar2.vel",DATAFLOAT,&data->radar2.vel);
	DataMapAddScalar(ptr,"radar2.vel_err",DATAFLOAT,&data->radar2.vel_err);
	DataMapAddScalar(ptr,"radar2.pwr",DATAFLOAT,&data->radar2.pwr);
	DataMapAddScalar(ptr,"radar2.w_l",DATAFLOAT,&data->radar2.w_l);
	DataMapAddScalar(ptr,"radar2.glat",DATAFLOAT,&data->radar2.glat);
	DataMapAddScalar(ptr,"radar2.glon",DATAFLOAT,&data->radar2.glon);
	DataMapAddScalar(ptr,"radar2.gazm",DATAFLOAT,&data->radar2.gazm);
	DataMapAddScalar(ptr,"radar2.mlat",DATAFLOAT,&data->radar2.mlat);
	DataMapAddScalar(ptr,"radar2.mlon",DATAFLOAT,&data->radar2.mlon);
	DataMapAddScalar(ptr,"radar2.mazm",DATAFLOAT,&data->radar2.mazm);
	DataMapAddScalar(ptr,"radar2.st_time",DATAINT,&data->radar2.st_time);
	DataMapAddScalar(ptr,"radar2.ed_time",DATAINT,&data->radar2.ed_time);


	DataMapAddScalar(ptr,"velg",DATAFLOAT,&data->velg);
	DataMapAddScalar(ptr,"velm",DATAFLOAT,&data->velm);
	DataMapAddScalar(ptr,"glat",DATAFLOAT,&data->glat);
	DataMapAddScalar(ptr,"glon",DATAFLOAT,&data->glon);
	DataMapAddScalar(ptr,"gazm",DATAFLOAT,&data->gazm);
	DataMapAddScalar(ptr,"mlat",DATAFLOAT,&data->mlat);
	DataMapAddScalar(ptr,"mlon",DATAFLOAT,&data->mlon);
	DataMapAddScalar(ptr,"mazm",DATAFLOAT,&data->mazm);
	DataMapAddScalar(ptr,"dgeo",DATAFLOAT,&data->dgeo);
	DataMapAddScalar(ptr,"dmag",DATAFLOAT,&data->dmag);

	DataMapAddScalar(ptr,"st_time",DATAINT,&data->st_time);
	DataMapAddScalar(ptr,"ed_time",DATAINT,&data->ed_time);

  return 0;
}

int MergeRead(int fid,struct MergeData *data)
{

  int s;
  struct DataMap *ptr;

  ptr=DataMapRead(fid);
  if (ptr==NULL) return -1;
  s=MergeDecode(ptr,data);
  DataMapFree(ptr);
  return s;
}
 
int MergeFRead(FILE *fp,struct MergeData *data)
{
  return MergeRead(fileno(fp),data);
}

int MergeWrite(int fid,struct MergeData *data)
{

  int s;
  struct DataMap *ptr=NULL;

  ptr=DataMapMake();
  if (ptr==NULL) return -1;

  s=MergeEncode(ptr,data);

  if (s==0)
	{
    if (fid !=-1) s=DataMapWrite(fid,ptr);
    else s=DataMapSize(ptr);
  }

  DataMapFree(ptr);
  return s;

}

int MergeFwrite(FILE *fp,struct MergeData *data)
{
  return MergeWrite(fileno(fp),data);
}



