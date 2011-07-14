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
#include "siteglobal.h"

#include "site.fhe.h"
#include "site.fhw.h"
#include "site.tst.h"

int SiteBuild(int stid) {
  switch (stid) {
     
  case 0:
    sitelib.start=SiteTstStart;
    sitelib.setupradar=SiteTstSetupRadar;
    sitelib.startscan=SiteTstStartScan;
    sitelib.startintt=SiteTstStartIntt;
    sitelib.fclr=SiteTstFCLR;
    sitelib.tmseq=SiteTstTimeSeq;
    sitelib.integrate=SiteTstIntegrate;
    sitelib.endscan=SiteTstEndScan;
    sitelib.exit=SiteTstExit;
    break;
  case 205:
    sitelib.start=SiteFheStart;
    sitelib.setupradar=SiteFheSetupRadar;
    sitelib.startscan=SiteFheStartScan;
    sitelib.startintt=SiteFheStartIntt;
    sitelib.fclr=SiteFheFCLR;
    sitelib.tmseq=SiteFheTimeSeq;
    sitelib.integrate=SiteFheIntegrate;
    sitelib.endscan=SiteFheEndScan;
    sitelib.exit=SiteFheExit;
    break;
  case 204:
    sitelib.start=SiteFhwStart;
    sitelib.setupradar=SiteFhwSetupRadar;
    sitelib.startscan=SiteFhwStartScan;
    sitelib.startintt=SiteFhwStartIntt;
    sitelib.fclr=SiteFhwFCLR;
    sitelib.tmseq=SiteFhwTimeSeq;
    sitelib.integrate=SiteFhwIntegrate;
    sitelib.endscan=SiteFhwEndScan;
    sitelib.exit=SiteFhwExit;
    break;
  default:
    return -1;
    break;
  }
  return 0;
}





