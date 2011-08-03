/* fit_demo.c
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
#include "fitblk.h"
#include "fitdata.h"
#include "radar.h"

#include "lmfit.h"
#include "fitacf.h"
#include "fitread.h"
#include "oldfitread.h"


#include "errstr.h"
#include "hlpstr.h"


/*********************************OVERVIEW********************************************
*
*	SuperDARN radar data is broken up into scans, usually 1 or 2 minutes in duration.
* A scan is broken up into some number of beams, usually 16+, numbered starting
* from 0.  The beams provide the azimuthal spatial coverage.  One "beam sounding"
* is when the radar sends out a signal along a certain azimuth, and waits for returns.
* the amount of time that the radar spends on that azimuth waiting for returns is
* called an integration period.  Each beam is broken up into some number of range gates,
* usually 75 or 100.  The range gates provide the radial spatial coverage.  Each
* range gate has a characteristic Dopper velocity, power, and Doppler spectral width.
*
*************************************************************************************/


/*radar operating parameter structure, 1 per beam sounding*/
struct RadarParm *prm;
/*fit data structure, 1 per beam sounding*/
struct FitData *fit;


struct RadarNetwork *network;
struct Radar *radar;
struct RadarSite *site;

struct OptionData opt;

int main(int argc,char *argv[])
{

  /* File format transistion
   * ------------------------
   *
   * When we switch to the new file format remove any reference
   * to "new". Change the command line option "new" to "old" and
   * remove "old=!new".
   */

	/*note about OLD and NEW:
	*
	* SuperDARN file formats changed on July 1, 2006.  Old file formats
	* are .dat (rawacf) and .fit (fitacf/fitex).  If you are processing a
	* file that is a .rawacf, .fitacf, or .fitex then you must invoke
	* the command line option -new.
	*/

	/*note about FITACF and FITEX
	*
	* fitacf is the standard superdarn fit file, processed with the
	* fitacf algorithm.  fitex is is the same format as fitacf, and can
	* be read/processed the same way, except the fitting was done
	* with the fitex2 algorithm, developed at VT.  Preliminary testing
	* has shown that this algorithm provides better results than then
	* the fitacf algorithm.
	*/


  unsigned char old=0;
  unsigned char new=0;

  char *envstr;
  int status;
  int arg,i;

  unsigned char help=0;
  unsigned char option=0;

  unsigned char vb=0;

  FILE *fitfp=NULL;
	FILE *fp=NULL;
  struct OldFitFp *oldfitfp=NULL;


	/*initialize the data structures*/
  prm=RadarParmMake();
  fit=FitMake();

	/*process command line options*/
  OptionAdd(&opt,"-help",'x',&help);
  OptionAdd(&opt,"-option",'x',&option);
  OptionAdd(&opt,"vb",'x',&vb);
  OptionAdd(&opt,"new",'x',&new);
  arg=OptionProcess(1,argc,argv,&opt,NULL);
  old=!new;
  if (help==1)
	{
    OptionPrintInfo(stdout,hlpstr);
    exit(0);
  }
  if (option==1)
	{
    OptionDump(stdout,&opt);
    exit(0);
  }
  if ((old) && (argc-arg<2))
	{
    OptionPrintInfo(stdout,hlpstr);
    exit(-1);
  }

  /*read radar tables, load radar information, must always be done*/
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

	/*now, lets actually read the fit file*/
	/*old format files (.fit) have to be read like this*/
	if(old)
	{
		oldfitfp=OldFitOpen(argv[arg],NULL);
		if(oldfitfp==NULL)
		{
			fprintf(stderr,"File not found.\n");
			exit(-1);
		}
		status = OldFitRead(oldfitfp,prm,fit);
	}
	/*new format files (.fitacf/.fitex) have to be read like this*/
	else
	{
		fitfp=fopen(argv[arg],"r");
		if (fitfp==NULL)
		{
			fprintf(stderr,"File not found.\n");
      exit(-1);
    }
    status = FitFread(fitfp,prm,fit);
	}

	/*get time-specific radar inromation*/
	radar=RadarGetRadar(network,prm->stid);
  if (radar==NULL)
	{
    fprintf(stderr,"Failed to get radar information.\n");
    exit(-1);
  }
  site=RadarYMDHMSGetSite(radar,prm->time.yr,prm->time.mo,
												prm->time.dy,prm->time.hr,prm->time.mt,prm->time.sc);

	do
	{
		/*now, lets examine some radar parameters*/
		fprintf(stdout,"Date: %d-%d-%d Time: %d:%d:%d Beam: %d\n",prm->time.yr,prm->time.mo,
	     prm->time.dy,prm->time.hr,prm->time.mt,prm->time.sc,prm->bmnum);

		fprintf(stdout,"Scan Flag (!= 0 indicates a new scan is starting) : %d\n",prm->scan);

		fprintf(stdout,"# of range gates : %d  Distance to First Range : %d km\n",prm->nrang,prm->lagfr);

		/*now, lets go through the range gates*/
		for(i=0;i<prm->nrang;i++)
		{
			/*check quality flag to see if range gate contains backscatter*/
			if(fit->rng[i].qflg)
				fprintf(stdout,"Range Gate : %d  Lag 0 Power : %lf  Power : %lf dB  Velocity : %lf m/s  Spectral Width : %lf m/s\n",
								i,fit->rng[i].p_0,fit->rng[i].p_l,fit->rng[i].v,fit->rng[i].w_l);
		}

		fprintf(stdout,"END OF BEAM SOUNDING RECORD\n\n\n");

		/*now, read the next record*/
		if(old)
			status = OldFitRead(oldfitfp,prm,fit);
		/*new format files (.fitacf/.fitex) have to be read like this*/
		else
			status = FitFread(fitfp,prm,fit);

	} while (status == 0);

	/*close the file pointer*/
  if(old)
		OldFitClose(oldfitfp);


	return 0;
}

	