/* fio.c
   =====
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>

char *FIOMakeFile(char *pathenv,int yr,int mo,int dy,int hr,int mt,int sc,
		  char *code,char *extra,char *ext,int mode,int flag) {
 
  char pathname[128]="/";
  char *fullname=NULL;
  char name[32];
  char *path;
  int file;
  int openflag;
 
  fullname=malloc(256);
  if (fullname==NULL) return NULL;

  if (mode==0) 
    mode=S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

  openflag=O_WRONLY | O_CREAT;
  if (flag==0) openflag|=O_EXCL;
  else if (flag==1) openflag|=O_TRUNC;    

  if (extra==NULL)  
    sprintf(name,"%04d%02d%02d.%02d%02d.%02d.%s",yr,mo,dy,hr,mt,sc,code);
  else 
    sprintf(name,"%04d%02d%02d.%02d%02d.%02d.%s.%s",
            yr,mo,dy,hr,mt,sc,code,extra);
 
  if (pathenv !=NULL) strncpy(pathname,pathenv,80);
  path = strtok(pathname, ":");	
  file = -1;
  while ((file == -1) && (path != NULL)) {
    sprintf(fullname,"%s/%s.%s",path,name,ext);      
    file = open(fullname,openflag,mode);
    path = strtok(NULL, ":");    
  }
   
  if (file != -1) {
    close(file);
    return fullname;
  }

  free(fullname);
  return NULL;
}
