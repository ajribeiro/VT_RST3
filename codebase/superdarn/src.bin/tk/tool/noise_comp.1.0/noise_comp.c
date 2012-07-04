/* make_fit.c
   ==========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.



*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <zlib.h>

#include "rtypes.h"
#include "option.h"

#include "dmap.h"
#include "rprm.h"
#include "rawdata.h"
#include "radar.h"

#include "rawread.h"

#include "errstr.h"
#include "hlpstr.h"



struct RadarParm *prm;
struct RawData *raw;
struct FitData *fit;
struct FitBlock *fblk;

struct RadarNetwork *network;
struct Radar *radar;
struct RadarSite *site;

struct OptionData opt;

int comp_dbl_cmp(const void *x,const void *y)
{
  double *a,*b;
  a=(double *) x;
  b=(double *) y;
  if (*a > *b) return 1;
  else if (*a == *b) return 0;
  else return -1;
}


void comp_noise_stat(struct RadarParm *prm, struct RawData * raw,
                double * skynoise)
{
  int j=0, R, i=0;
  double * pwrd = malloc(prm->nrang*sizeof(double));
  if(prm->cp != -3310 && prm->cp != 3310 && prm->cp != 503 && prm->cp != -503)
  {
    j=0;
    for(R=0;R<prm->nrang;R++)
    {
      pwrd[j] = sqrt(raw->acfd[0][R*prm->mplgs]*raw->acfd[0][R*prm->mplgs]);
      if(pwrd[j] > 0.)
        j++;
    }
    qsort(pwrd, j, sizeof(double), comp_dbl_cmp);
    if(j >= 80)
    {
      for(i=0;i<80;i++)
        *skynoise += pwrd[i];
      *skynoise /= 80.;
    }
    else
    {
      for(i=0;i<j;i++)
        *skynoise += pwrd[i];
      *skynoise /= (double)j;
    }
    if(*skynoise <= 1.) *skynoise = prm->noise.search;
  }
  else
    *skynoise = prm->noise.search;

  return;
}


int main(int argc,char *argv[])
{

  /* File format transistion
   * ------------------------
   *
   * When we switch to the new file format remove any reference
   * to "new". Change the command line option "new" to "old" and
   * remove "old=!new".
   */


  unsigned char new=0;

  char *envstr;
  int status;
  int arg,i;

  unsigned char help=0;
  unsigned char option=0;

  unsigned char vb=0;

  FILE *fp=NULL;


  prm=RadarParmMake();
  raw=RawMake();

  OptionAdd(&opt,"-help",'x',&help);
  OptionAdd(&opt,"-option",'x',&option);
  OptionAdd(&opt,"vb",'x',&vb);
  OptionAdd(&opt,"new",'x',&new);

  arg=OptionProcess(1,argc,argv,&opt,NULL);

  envstr=getenv("SD_RADAR");
  if (envstr==NULL)
	{
    fprintf(stderr,"Environment variable 'SD_RADAR' must be defined.\n");
    exit(-1);
  }

  fp=fopen(envstr,"r");

  if (fp==NULL)
	{
    fprintf(stderr,"Could not locate radar information file.\n");
    exit(-1);
  }

  network=RadarLoad(fp);
  fclose(fp);
  if (network==NULL)
	{
    fprintf(stderr,"Failed to read radar information.\n");
    exit(-1);
  }

  envstr=getenv("SD_HDWPATH");
  if (envstr==NULL)
	{
    fprintf(stderr,"Environment variable 'SD_HDWPATH' must be defined.\n");
    exit(-1);
  }

  RadarLoadHardware(envstr,network);

	fp=fopen(argv[arg],"r");
	if (fp==NULL)
	{
		fprintf(stderr,"File not found.\n");
		exit(-1);
	}
	status=RawFread(fp,prm,raw);

  radar=RadarGetRadar(network,prm->stid);
  if (radar==NULL)
	{
    fprintf(stderr,"Failed to get radar information.\n");
    exit(-1);
  }

  site=RadarYMDHMSGetSite(radar,prm->time.yr,prm->time.mo,
		          prm->time.dy,prm->time.hr,prm->time.mt,
                          prm->time.sc);

  if (site==NULL)
	{
    fprintf(stderr,"Failed to get site information.\n");
    exit(-1);
  }



  if (vb)
      fprintf(stderr,"%d-%d-%d %d:%d:%d beam=%d\n",prm->time.yr,prm->time.mo,
	     prm->time.dy,prm->time.hr,prm->time.mt,prm->time.sc,prm->bmnum);

  do
  {
		if (vb)
      fprintf(stderr,"%d-%d-%d %d:%d:%d beam=%d\n",prm->time.yr,prm->time.mo,
	     prm->time.dy,prm->time.hr,prm->time.mt,prm->time.sc,prm->bmnum);
		double tot_noise = 0.;
		long ngates = 0;
		double skynoise = 0;
		if(prm->time.hr == 18)
		{
			/*calculate noise levels*/
			comp_noise_stat(prm,raw,&skynoise);
			for(i=70;i<prm->nrang;i++)
			{
				tot_noise += raw->acfd[0][i*prm->mplgs];
				ngates++;
			}
			fprintf(stderr,"%lf  %lf  %lf\n",prm->noise.search,skynoise,tot_noise/ngates);
		}

    status=RawFread(fp,prm,raw);

  } while (status==0);

  return 0;
}













