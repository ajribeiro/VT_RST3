/* set_schedule.c
   ==============
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "rtime.h"
#include "log_info.h"
#include "schedule.h"

int set_schedule(struct scd_blk *ptr) {
  int yr,mo,dy,hr,mt,sc,us;
  double stime;
  int c;
  TimeReadClock(&yr,&mo,&dy,&hr,&mt,&sc,&us);
  stime=TimeYMDHMSToEpoch(yr,mo,dy,hr,mt,sc);
  
  for (c=0;(c<ptr->num) && (ptr->entry[c].stime<=stime);c++);
  return c;  
}
