/* schedule.h
   ==========
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/


/* data structures for my scheduler routine */

#define SCHED_LINE_LENGTH 1024
#define SCHED_MAX_ENTRIES 1024
#define DELIM " \t\n"

/* each entry consists of time at which a command starts 
   + the load command */

struct scd_entry {
  double stime;
  char command[SCHED_LINE_LENGTH];
};

struct scd_blk {
  char name[256];
  int num; /* number of scheduled events */
  int cnt;
  char path[SCHED_LINE_LENGTH];
  struct scd_entry entry[SCHED_MAX_ENTRIES];
  char command[SCHED_LINE_LENGTH];
  int refresh;
  pid_t pid;
}; 
 
  
  
void print_schedule(struct scd_blk *ptr);
int set_schedule(struct scd_blk *ptr);
int load_schedule(FILE *fp,struct scd_blk *ptr);
int test_schedule(struct scd_blk *ptr);
