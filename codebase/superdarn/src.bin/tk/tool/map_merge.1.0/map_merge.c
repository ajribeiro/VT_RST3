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
#include "mlt.h"

struct RadarNetwork *network;
struct Radar *radar1;
struct Radar *radar2;
struct RadarSite *site1;
struct RadarSite *site2;
struct OptionData opt;

struct combvec
{
  int matched;
  double diff;
};

double haversine(double theta)
{
  return sin(theta/2.)*sin(theta/2.);
}

/*convert year/month/day to day of year*/
int yrmondaytodoy(int y,int m,int d)
{
  int i;
  int doy = 0;
  int monarr[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

  if((y % 4) == 0)
    monarr[1] = 29;


  for(i=0;i<m-1;i++)
  {
    doy += monarr[i];
  }
  doy += (d-1);
  return doy;
}

double getazm(double lat1, double lon1, double lat2, double lon2)
{
  return atan2(sin(lon2-lon1)*cos(lat2),cos(lat1)*sin(lat2)-sin(lat1)*cos(lat2)*cos(lon2-lon1));
}

void getendpoints(double lat1,double lon1,double * lat2, double * lon2, double azm)
{
  double d = 25./6378.,pi=3.14159,degrad=3.14159/180.,q,tlat2,tlon2;
  lat1 *= degrad;
  lon1 *= degrad;
  azm *= degrad;
  double dLat = d*cos(azm);
  tlat2 = lat1 + dLat;
  double dPhi = log(tan(tlat2/2.+pi/4.)/tan(lat1/2.+pi/4.));
  if(dPhi != 0.) q = dLat/dPhi;
  else q = cos(lat1);

  if(fabs(tlat2) > pi/2.)
  {
    if(tlat2 > 0) tlat2 = pi-tlat2;
    else tlat2 = -(pi-tlat2);
  }

  double dLon = d*sin(azm)/q;
  int wrap = (int)((lon1+dLon+pi)/(2.*pi));
  tlon2 = (lon1+dLon+pi)-(double)wrap*(2.*pi) - pi;

  *lon2 = tlon2/degrad;
  *lat2 = tlat2/degrad;
}

int main(int argc,char *argv[])
{
  /*declarations*/
  int arg = 0, i, j, k, mltbin, mlatbin;
  double sc, vel, azm, num, mlt;
  int yr, mo, dy, hr, mn;
  double pi = 3.14159;
  FILE *fp;
  FILE *mergefp = NULL;
  char *envstr;
  unsigned char help = 0;
  unsigned char option = 0;
  int s,vb=0;

	double *** pattern = malloc(96*sizeof(double **));
	for(i=0;i<96;i++)
	{
		pattern[i] = malloc(45*sizeof(double *));
		for(j=0;j<45;j++)
		{
			pattern[i][j] = malloc(3*sizeof(double));
			for(k=0;k<3;k++)
			{
				pattern[i][j][k] = 0;
			}
		}
	}

	FILE * convection = fopen("/rst/output_files/mconv.txt","r");
	if(convection != NULL)
	{
		for(i=0;i<96;i++)
			for(j=0;j<45;j++)
			{
				s = fscanf(convection,"%*d  %*d  %lf  %lf  %lf\n",&vel,&azm,&num);
				if(num != 0.)
				{
					pattern[i][j][0] = vel*num;
					pattern[i][j][1] = azm*num;
					pattern[i][j][2] = num;
				}
			}
		fclose(convection);
	}


	/*without this, we get an undefined reference to dataMapRead and dataMapFree, no idea why*/
  struct RadarParm *tempprm1 = RadarParmMake();

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


	struct MergeData * myData = malloc(sizeof(struct MergeData));
  /*read the first radar's file*/
  mergefp=fopen(argv[arg],"r");
  fprintf(stderr,"%s\n",argv[arg]);
  if(mergefp==NULL)
  {
    fprintf(stderr,"File %s not found.\n",argv[arg]);
    exit(-1);
  }

	s=MergeFread(mergefp,myData);


  radar1=RadarGetRadar(network,myData->radar1.stid);
  if (radar1==NULL)
  {
    fprintf(stderr,"Failed to get radar information.\n");
    exit(-1);
  }
  TimeEpochToYMDHMS(myData->radar1.st_time,&yr,&mo,&dy,&hr,&mn,&sc);
  site1=RadarYMDHMSGetSite(radar1,yr,mo,dy,hr,mn,sc);

  radar2=RadarGetRadar(network,myData->radar2.stid);
  if (radar2==NULL)
  {
    fprintf(stderr,"Failed to get radar information.\n");
    exit(-1);
  }
  TimeEpochToYMDHMS(myData->radar2.st_time,&yr,&mo,&dy,&hr,&mn,&sc);
  site2=RadarYMDHMSGetSite(radar2,yr,mo,dy,hr,mn,sc);

	do
	{
		TimeEpochToYMDHMS(myData->st_time,&yr,&mo,&dy,&hr,&mn,&sc);
		mlt = MLTConvertEpoch((double)myData->st_time,myData->mlon);
		mltbin = ((int)(mlt*4.+.5) % 96);
		mlatbin = ((int)(myData->mlat/2.+.5) % 45);
		pattern[mltbin][mlatbin][0] += myData->velm*sin(myData->mazm*pi/180.);
		pattern[mltbin][mlatbin][1] += myData->velm*cos(myData->mazm*pi/180.);
		if(mltbin == 95 && mlatbin == 27)
		{
			fprintf(stderr,"%lf  %lf  %lf  %f\n",myData->velm,myData->mazm,myData->velm*sin(myData->mazm*pi/180.),myData->velm*cos(myData->mazm*pi/180.));
			fprintf(stderr,"%lf  %lf  %lf\n",pattern[mltbin][mlatbin][0],pattern[mltbin][mlatbin][1],pattern[mltbin][mlatbin][2]);
		}
		pattern[mltbin][mlatbin][2] += 1.;

		s=MergeFread(mergefp,myData);
	} while (s == 0);

	fclose(mergefp);
	free(myData);

	convection = fopen("/rst/output_files/mconv.txt","w");
	if(convection != NULL)
	{
		for(i=0;i<96;i++)
			for(j=0;j<45;j++)
			{
				if(pattern[i][j][2] != 0.)
					fprintf(convection,"%d  %d  %lf  %lf  %lf\n",i,j,pattern[i][j][0]/pattern[i][j][2],pattern[i][j][1]/pattern[i][j][2],pattern[i][j][2]);
				else
					fprintf(convection,"%d  %d  %lf  %lf  %lf\n",i,j,0.,0.,0.);
			}
		fclose(convection);
	}

	for(i=0;i<96;i++)
	{
		for(j=0;j<45;j++)
			free(pattern[i][j]);
		free(pattern[i]);
	}
	free(pattern);

  return 0;
}
