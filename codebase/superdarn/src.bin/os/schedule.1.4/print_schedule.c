/* print_schedule.c
   ================
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


void print_schedule(struct scd_blk *ptr) {/* prints out the schedule */
  int c;
  char txt[256];
  if (ptr->num==0) {
    log_info(1,"No schedule file loaded");
    return;
  }
  
  sprintf(txt,"Schedule file %s loaded",ptr->name);
  log_info(1,txt);
  sprintf(txt,"Command path -> %s",ptr->path);
  log_info(1,txt);
  if (ptr->entry[0].stime==-1) {
    sprintf(txt,"Default Program -> %s\n",ptr->entry[0].command);
    log_info(1,txt);
  }
  if ((ptr->cnt >0) && (ptr->cnt<ptr->num)) {
    int yr,mo,dy,hr,mt;
    double sc;
    log_info(1,"Pending programs :\n");    		 
    for (c=ptr->cnt;c<ptr->num;c++) {
      if (ptr->entry[c].stime==-1) continue;
      TimeEpochToYMDHMS(ptr->entry[c].stime,&yr,&mo,&dy,&hr,&mt,&sc);
      sprintf(txt,"%d : %d %d %d : %d %d -> %s",c,yr,mo,dy,hr,mt,
	          ptr->entry[c].command);
      log_info(1,txt);       
    } 
  } else log_info(1,"There are no pending programs");
  sprintf(txt,"\nCurrent program ->%s",ptr->command);
  log_info(1,txt);
  sprintf(txt,"Schedule reloaded every %d seconds",ptr->refresh);
  
  log_info(1,txt);
}  			
