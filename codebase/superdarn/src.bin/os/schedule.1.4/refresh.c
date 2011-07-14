/* refresh.c
   =========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "rtime.h"
#include "log_info.h"
#include "schedule.h"

int then=-1;
time_t tval=-1;


int test_refresh(struct scd_blk *ptr) {

  struct stat buf;
  int yr,mo,dy,hr,mt,sc,us;
  int nowsec,now,rc;
  TimeReadClock(&yr,&mo,&dy,&hr,&mt,&sc,&us);
  
  nowsec=hr*3600+mt*60+sc;
  now=nowsec/ptr->refresh;

  /* test to see if the schedule has been altered */

  if ((rc=stat(ptr->name,&buf)) !=0) return -1;
  if (tval==-1) tval=buf.st_mtime;
  if (buf.st_mtime !=tval) {
    tval=buf.st_mtime;
    then=now;
    return 1;
  }


  /* okay check whether we're on a refresh boundary */
  
  if (then==-1) then=now;
  if (then !=now) {
    tval=buf.st_mtime;
    then=now;
    return 1;
  }   

 

  
  return 0;
}
