/* reopen.c
   ======== 
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <zlib.h>
#include "rtypes.h"
#include "limit.h"
#include "dmap.h"
#include "radar.h"
#include "rprm.h"
#include "iq.h"
#include "rawdata.h"
#include "fitblk.h"
#include "fitdata.h"
#include "global.h"

static int then=-1;

int OpsReOpen(int hbnd,int mtbnd,int scbnd) {

  int bndsec;
  int nowsec;
  int now;

  bndsec=hbnd*3600+60*mtbnd+scbnd;
  nowsec=hr*3600+60*mt+sc;
  
  now=nowsec/bndsec;
  if (then==-1) then=now;
  if (then !=now) {
    then=now;
    return 1;
  }
  return 0;
}



 
