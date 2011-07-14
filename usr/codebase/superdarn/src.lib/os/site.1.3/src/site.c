/* site.c
   ====== 
   Author R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include "rtypes.h"
#include "limit.h"
#include "tsg.h"
#include "maketsg.h"
#include "acf.h"
#include "tcpipmsg.h"
#include "rosmsg.h"
#include "shmem.h"
#include "global.h"
#include "site.h"

int sock;
char server[256];
int port;
int num_transmitters;
struct timeval tock;
struct ControlPRM rprm;
struct ControlData rdata;
struct BadTR badtrdat;
struct TXStatus txstatus;
struct SiteLibrary sitelib;
int *exit_flag=NULL;
int cancel_count=0;




int SiteStart() {
  return (sitelib.start)();
}

int SiteSetupRadar() {
  return (sitelib.setupradar)();
}
 
int SiteStartScan() {
  return (sitelib.startscan)();
}

int SiteStartIntt(int sec,int usec) {
  return (sitelib.startintt)(sec,usec);
}

int SiteFCLR(int stfreq,int edfreq) {
  return (sitelib.fclr)(stfreq,edfreq);
}

int SiteTimeSeq(int *ptab) {
  return (sitelib.tmseq)(ptab);
}

int SiteIntegrate(int (*lags)[2]) {
  return (sitelib.integrate)(lags);
}

int SiteEndScan(int bsc,int bus) {
  return (sitelib.endscan)(bsc,bus);
}

void SiteExit(int signo) {
  (sitelib.exit)(signo);
}




