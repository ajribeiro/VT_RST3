/* load_schedule.c
   ===============
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
#include "schedule.h"
#include "log_info.h"

int parse_schedule_line(char *line,struct scd_blk *ptr) {
 
  char *token;
  int year,month,day,hour,minute,i;
  if ((token=strtok(line,DELIM))==NULL) return -1; /* year/default */
  
  if (strcmp(token,"default")==0) {
    /* default entry */
    if ((token=strtok(NULL,""))==NULL) return -1; /* command */
    strcpy(ptr->entry[ptr->num].command,token);
    ptr->entry[ptr->num].stime=-1;
	ptr->num++;
    return 1;
  } else if (strcmp(token,"path")==0) {
    /* the path variable */
    if ((token=strtok(NULL,""))==NULL) return -1; /* command */
    strcpy(ptr->path,token);
  } else {
    /* extract time data */
	year=atoi(token);
    if ((token=strtok(NULL,DELIM))==NULL) return -1; /* month */
	month=atoi(token);
    if ((token=strtok(NULL,DELIM))==NULL) return -1; /* day */
    day=atoi(token);
    if ((token=strtok(NULL,DELIM))==NULL) return -1; /* hour */
	hour=atoi(token);
    if ((token=strtok(NULL,DELIM))==NULL) return -1; /* minute */
	minute=atoi(token);
    ptr->entry[ptr->num].stime=TimeYMDHMSToEpoch(year,month,day,hour,minute,0);
    if (ptr->entry[ptr->num].stime==-1) return -1;
    if ((token=strtok(NULL,""))==NULL) return -1; /* command */
        
    /* strip leading spaces from command */
    for (i=0;(token[i] !=0) && ((token[i]==' ') || (token[i]=='\t'));i++); 
    if (token[i]==0) return -1;   
    strcpy(ptr->entry[ptr->num].command,token+i);
    ptr->num++;
  }
  return 0;	
}
				 
int cmp_scd(const void *a,const void *b) {
  struct scd_entry *as;
  struct scd_entry *ab;

   as=(struct scd_entry *) a;
   ab=(struct scd_entry *) b;
  
   if (as->stime<ab->stime) return -1;
   if (as->stime>ab->stime) return 1;
   return 0;
}

int load_schedule(FILE *fp,struct scd_blk *ptr) {
  int chr;
  int count=0;
  char txt[128];
  char line[SCHED_LINE_LENGTH];
  int default_present=0;
    
  ptr->num=0;
  ptr->cnt=0;
  while ( ( (chr=fgetc(fp)) != EOF) && 
          (ptr->num<SCHED_MAX_ENTRIES) ) {
    switch (chr) {
     case '#' :
	    /* comment so ignore rest of line */
		while ( ((chr=fgetc(fp)) != EOF) && (chr !='\n'));  
		break;
	 case '\n' :
	    /* ignore new lines */
		break;
	 case ' ' :
	   /* ignore leading spaces */
	   break;		
	 default : 
	   /* build string */
	   line[0]=(char) chr;
	   count=1;
	   while ( (count<SCHED_LINE_LENGTH) && ( (chr=fgetc(fp)) != EOF) && 
	   			(chr !='\n') ) {
		 line[count]=(char) chr;		
	     count++;
	   }
	   line[count]=0;
	   if (parse_schedule_line(line,ptr)==1) default_present=1;
	   break;
	}	
  }
 	
  if (ptr->num==0) {
    log_info(0,"No programs in schedule");
    return -1;
  }
  if (default_present==0) {
    log_info(0,"No default program in schedule");
    return -1;
  }

  if (ptr->num >= SCHED_MAX_ENTRIES) {
    sprintf(txt,"Schedule truncated : > %d entries",SCHED_MAX_ENTRIES);
    log_info(0,txt);
  }
  /* sort the events into order */
  qsort(ptr->entry,ptr->num,sizeof(struct scd_entry),cmp_scd);						    
  return 0;
}
