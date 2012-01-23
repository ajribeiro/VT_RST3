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
#include "fitdata.h"
#include "fitread.h"
#include "scandata.h"
#include "fitscan.h"
#include "mergedata.h"
#include "mergewrite.h"
#include "mergeread.h"

struct RadarNetwork *network;
struct Radar *radar_rad;
struct Radar *radar_ray;
struct RadarSite *site_rad;
struct RadarSite *site_ray;
struct OptionData opt;


int main(int argc,char *argv[])
{
  /*declarations*/
  int arg = 0, vb = 0;
  int i,j;
  FILE *fp;
  FILE *fitfp_rad = NULL;
  FILE *fitfp_ray = NULL;
  char *envstr;
  unsigned char help = 0;
  unsigned char option = 0;
  int s1 = 0, s2 = 0;
	int double st_time,ed_time,rad_time;

  struct FitData *fit_rad = FitMake();
	struct FitData *fit_ray = FitMake();
  struct RadarParm *prm_rad = RadarParmMake();
	struct RadarParm *prm_ray = RadarParmMake();
	struct FitData *fit_ray_next = FitMake();
	struct RadarParm *prm_ray_next = RadarParmMake();


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


  /*open the radar's file*/
  fitfp_rad=fopen(argv[arg],"r");
  fprintf(stderr,"%s\n",argv[arg]);
  if(fitfp_rad==NULL)
  {
    fprintf(stderr,"File %s not found.\n",argv[arg]);
    exit(-1);
  }

	/*read the first radar record*/
	FitFread(fitfp_rad,prm_rad,fit_rad);

	/*get radar information for the real radar*/
  radar_rad=RadarGetRadar(network,prm_rad->stid);
  if (radar_rad==NULL)
  {
    fprintf(stderr,"Failed to get radar information.\n");
    exit(-1);
  }
  site_rad=RadarYMDHMSGetSite(radar_rad,prm_rad->time.yr,prm_rad->time.mo,prm_rad->time.dy,
															prm_rad->time.hr,prm_rad->time.mt,prm_rad->time.sc);

	rad_time = TimeYMDHMSToEpoch(prm_rad->time.yr,prm_rad->time.mo,prm_rad->time.dy,
															prm_rad->time.hr,prm_rad->time.mt,prm_rad->time.sc);

	/*open the raytracing file*/
  fitfp_ray=fopen(argv[arg+1],"r");
  fprintf(stderr,"%s\n",argv[arg]);
  if(fitfp_ray==NULL)
  {
    fprintf(stderr,"File %s not found.\n",argv[arg+1]);
    exit(-1);
  }

	/*read the first raytracing record*/
	FitFread(fitfp_ray,prm_ray,fit_ray);

	/*get radar information for the raytracing radar*/
  radar_ray=RadarGetRadar(network,prm_ray->stid);
  if (radar_ray==NULL)
  {
    fprintf(stderr,"Failed to get radar information.\n");
    exit(-1);
  }
  site_ray=RadarYMDHMSGetSite(radar_ray,prm_ray->time.yr,prm_ray->time.mo,prm_ray->time.dy,
															prm_ray->time.hr,prm_ray->time.mt,prm_ray->time.sc);
	st_time = TimeYMDHMSToEpoch(prm_ray->time.yr,prm_ray->time.mo,prm_ray->time.dy,
															prm_ray->time.hr,prm_ray->time.mt,prm_ray->time.sc);

	/*read the first second record*/
	FitFread(fitfp_ray,prm_ray_next,fit_ray_next);

	ed_time = TimeYMDHMSToEpoch(prm_ray_next->time.yr,prm_ray_next->time.mo,prm_ray_next->time.dy,
															prm_ray_next->time.hr,prm_ray_next->time.mt,prm_ray_next->time.sc);

	do
	{
		/*if we have overlapping times*/

	} while(s1 == 0 && s2 == 0);

	fclose(fitfp_rad);
	fclose(fitfp_ray);
  return 0;
}
