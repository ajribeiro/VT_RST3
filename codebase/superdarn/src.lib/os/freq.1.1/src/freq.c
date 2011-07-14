/* freq.c
   ======
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "freq.h"

struct FreqTable *FreqLoadTable(FILE *fp) {
  char line[1024];
  char *tkn;
  int i,j;
  int s,e,status;
  struct FreqTable *ptr;
  ptr=malloc(sizeof(struct FreqTable));
  if (ptr==NULL) return NULL;

  /*start scanning records from the file*/ 

  ptr->dfrq=DEFAULT_FREQ;
  ptr->num=0;
  ptr->start=NULL;
  ptr->end=NULL;
  while (fgets(line,1024,fp) !=0) {
    for (i=0; (line[i] !=0) && 
              ((line[i] ==' ') || (line[i]=='\n'));i++);

    /* ignore comments or empty lines */

    if ((line[i]==0) || (line[i]=='#')) continue;

    tkn=line+i; 
    if ((tkn[0]=='d') || (tkn[0]=='D')) { /* default frequency */
      for (j=0;(tkn[j] !='=') && (tkn[j] !=0);j++);
      if (tkn[j] !=0) {
        ptr->dfrq=atoi(tkn+j+1);
        if (ptr->dfrq==0) ptr->dfrq=DEFAULT_FREQ;
      }
      continue;      
    }
    status=sscanf(tkn,"%d %d",&s,&e);
    if (status==2) {
      if (ptr->start==NULL) ptr->start=malloc(sizeof(int));
      else ptr->start=realloc(ptr->start,sizeof(int)*(ptr->num+1));
      if (ptr->end==NULL) ptr->end=malloc(sizeof(int));
      else ptr->end=realloc(ptr->end,sizeof(int)*(ptr->num+1));
      ptr->start[ptr->num]=s;
      ptr->end[ptr->num]=e;
      ptr->num++;  
    }
 
  }
  return ptr;
}

int FreqTest(struct FreqTable *ptr,int freq) { 
  int i;
  if ((freq<8000) || (freq>20000)) return 1;
  if (ptr==0) return 0;
  if (ptr->num==0) return 0;

  for (i=0;i<ptr->num;i++) 
    if ((ptr->start[i]<=freq) && (freq<=ptr->end[i])) return 1;

  return 0;  
}
  

	   	
