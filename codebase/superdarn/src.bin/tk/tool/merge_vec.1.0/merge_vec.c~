/*
$Log: map_merge.c,v $

Revision 1.0  2009/03/03 17:05:20  aj
this code reads in a fit file and produces an ascii file

*/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
#include <zlib.h>
#include "rtypes.h"
#include "dmap.h"
#include "option.h"
#include "rtime.h"
#include "radar.h"
#include "rprm.h"
#include "invmag.h"
#include "rpos.h"
#include "fitdata.h"
#include "fitread.h"
#include "scandata.h"
#include "fitscan.h"
#include "mergedata.h"
#include "mergeread.h"

struct RadarNetwork *network;
struct Radar *radar1;
struct Radar *radar2;
struct RadarSite *site;
struct OptionData opt;

int main(int argc,char *argv[])
{
  /*declarations*/
  int arg = 0;
  double pi = 3.14159;
  FILE *fp;
  FILE *mfp = NULL;
  char *envstr;
  unsigned char help = 0;
  unsigned char option = 0;
  int s = 0, vb=0;


  envstr=getenv("SD_RADAR");
  if(envstr==NULL)
  {
    fprintf(stderr,"Environment variable 'SD_RADAR' must be defined.\n");
    return -1;
  }
  fp=fopen(envstr,"r");

  if(fp==NULL)
  {
    fprintf(stderr,"Could not locate radar information file.\n");
    exit(-1);
  }

  network=RadarLoad(fp);
  fclose(fp);
  if(network==NULL)
  {
    fprintf(stderr,"Failed to read radar information.\n");
    exit(-1);
  }

  envstr=getenv("SD_HDWPATH");
  if(envstr==NULL)
  {
    fprintf(stderr,"Environment variable 'SD_HDWPATH' must be defined.\n");
    exit(-1);
  }

  RadarLoadHardware(envstr,network);

  /*add options to control performance*/
  OptionAdd(&opt,"-help",'x',&help);
  OptionAdd(&opt,"-option",'x',&option);
  OptionAdd(&opt,"vb",'x',&vb);

  /*process the options*/
  arg=OptionProcess(1,argc,argv,&opt,NULL);
  if(option == 1)
  {
    OptionDump(stdout,&opt);
    exit(0);
  }


	struct MergeData * data = malloc(sizeof(struct MergeData));
	memset(data,0,sizeof(struct MergeData));

	mfp=fopen(argv[arg],"r");
	fprintf(stderr,"%s\n",argv[arg]);
	if(fp==NULL)
  {
    fprintf(stderr,"File %s not found.\n",argv[arg]);
    exit(-1);
  }

	MergeFread(mfp,data);

  radar1=RadarGetRadar(network,data->radar1.stid);
  if (radar1==NULL)
  {
    fprintf(stderr,"Failed to get radar information.\n");
    exit(-1);
  }

  radar2=RadarGetRadar(network,data->radar2.stid);
  if (radar1==NULL)
  {
    fprintf(stderr,"Failed to get radar information.\n");
    exit(-1);
  }


	fclose(mfp);
	free(data);

  return 0;
}
