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
<<<<<<< HEAD
#include <math.h> 
=======
#include <math.h>
>>>>>>> fitcomp
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
  int arg = 0, s, mag_flg = 0;
  FILE *fp;
  FILE *mergefp = NULL;
	FILE *out = NULL;
  char *envstr;
  unsigned char help = 0;
  unsigned char option = 0;
  int vb = 0;
	char * outfile = "/rst/output_files/mergevec.out.txt";
	double sc,jTime;
	int yr,mo,dy,hr,mt;

	struct MergeData myData;

	/*without this, get undefined ref to datamapread and datamapfree*/
	/*NO IDEA WHY THIS IS HAPPENING!!!!*/
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
	OptionAdd(&opt,"mag",'x',&mag_flg);

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
	s = MergeFread(mergefp,&myData);
	if(s == -1)
	{
		fprintf(stderr,"File %s is empty\n",argv[arg]);
    exit(-1);
	}
	out = fopen(outfile,"w");
	fprintf(out,"%d  %d  %d\n",mag_flg,myData.radar1.stid,myData.radar2.stid);

	do
	{

		TimeEpochToYMDHMS((double)myData.st_time,&yr,&mo,&dy,&hr,&mt,&sc);
		jTime = TimeYMDHMSToJulian(yr,mo,dy,hr,mt,sc);

		if(mag_flg)
			fprintf(out,"%lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf\n",
							myData.radar1.vel,myData.radar1.pwr,myData.radar1.w_l,myData.radar1.mlat,myData.radar1.mlon,myData.radar1.mazm,
							myData.radar2.vel,myData.radar2.pwr,myData.radar2.w_l,myData.radar2.mlat,myData.radar2.mlon,myData.radar2.mazm,
							myData.velm,myData.mlat,myData.mlon,myData.mazm,jTime);
		else
			fprintf(out,"%lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf\n",
							myData.radar1.vel,myData.radar1.pwr,myData.radar1.w_l,myData.radar1.glat,myData.radar1.glon,myData.radar1.gazm,
							myData.radar2.vel,myData.radar2.pwr,myData.radar2.w_l,myData.radar2.glat,myData.radar2.glon,myData.radar2.gazm,
							myData.velg,myData.glat,myData.glon,myData.gazm,jTime);

		s = MergeFread(mergefp,&myData);
<<<<<<< HEAD
		
=======

>>>>>>> fitcomp
	} while (s == 0);


	fclose(mergefp);
	fclose(out);

  return 0;
}
