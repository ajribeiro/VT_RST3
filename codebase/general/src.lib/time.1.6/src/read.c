/* read.c
   ======
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>



void TimeReadClock(int *yr,int *month,int *day,int *hour,int *min,int *sec,
		   int *usec) {


  struct timeval tv;

  time_t tm;
  struct tm *gmt_time;
  int s;


  s=gettimeofday(&tv,NULL);

  tm=tv.tv_sec;
  gmt_time = gmtime(&tm);
  *yr = gmt_time->tm_year + 1900;
  *month = gmt_time->tm_mon + 1;
  *day = gmt_time->tm_mday; 
  *hour = gmt_time->tm_hour;
  *min = gmt_time->tm_min;
  *sec = gmt_time->tm_sec;
  *usec = tv.tv_usec;
}  
