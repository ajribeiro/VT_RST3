/*
$Log: combvec.c,v $

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
#include "mergedata.h"
#include "mergewrite.h"
#include "mergeread.h"

struct OptionData opt;
struct RadarNetwork *network;



int main(int argc,char *argv[])
{
  /*declarations*/
  int arg = 0;
  double grho, lat1, lat2, lon1, lon2;
  double azm1, azm2, del_lat, del_lon, h, d, v_e, v_n, v1, v2, theta1, theta2, sc;
  int j, k, l, m, p, yr, mo, dy, hr, mn,sflg=0,temp;
  double pi = 3.14159;
  FILE *fp;
  FILE *mergefp = NULL;
  char *envstr;
  unsigned char help = 0;
  unsigned char option = 0;
  double azm,elv;
  int sthr = -1, edhr = 26;
  int vb = 0;

	struct MergeData myData;

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

  fprintf(stderr,"%s\n",argv[arg]);
	mergefp = fopen(argv[arg],"r");
	if(mergefp==NULL)
  {
    fprintf(stderr,"File %s not found.\n",argv[arg]);
    exit(-1);
  }
	MergeFread(stdin,&myData);

	fclose(mergefp);

  return 0;
}
