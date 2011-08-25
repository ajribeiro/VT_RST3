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
#include "mergewrite.h"

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



