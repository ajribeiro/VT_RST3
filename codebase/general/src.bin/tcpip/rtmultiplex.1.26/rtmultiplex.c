/* rtmultiplex.c
   =============
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "rtypes.h"
#include "option.h"
#include "connex.h"

#include "loginfo.h"
#include "errstr.h"
#include "hlpstr.h"
#include "pipe.h"
#include "fork.h"





#define MAXSERVER 32

int num=0;
char host[MAXSERVER][256];
int remoteport[MAXSERVER];
int sock[MAXSERVER];
time_t tick[MAXSERVER];

time_t pipewait=0;

unsigned  char *buffer[MAXSERVER];
int size[MAXSERVER];
int flag[MAXSERVER];



int outpipe=-1;
int resetflg=0;

char pname[256]={"port.id"};
char pidname[256]={"pid.id"};
char logfname[256]={"web.rt.log"};
char timefname[256]={"time.rt"};
unsigned char vb=0;


struct OptionData opt;

void trappipe(int signal) {
  close(outpipe);
  outpipe=-1;
}

int main(int argc,char *argv[]) {
  int arg;
  int c;
  unsigned char help=0;
  unsigned char option=0;

  char *logstr=NULL;
  char *timestr=NULL;
  char *pnamestr=NULL;
  char *pidstr=NULL;

  int port=0;
  int timeout=20;
  int status;
  char logbuf[256];

  int num=0;
  char host[MAXSERVER][256];
  int remoteport[MAXSERVER];
  int sock[MAXSERVER];

  unsigned char sfilter;
  unsigned char st;


  sigset_t set;
  struct sigaction act;

  struct timeval tmout;
  int cnt=0;
 
  OptionAdd(&opt,"-help",'x',&help);
  OptionAdd(&opt,"-option",'x',&option);

  OptionAdd(&opt,"vb",'x',&vb);
  OptionAdd(&opt,"t",'i',&timeout);
  OptionAdd(&opt,"lp",'i',&port);
  OptionAdd(&opt,"L",'t',&logstr);
  OptionAdd(&opt,"T",'t',&timestr);

  OptionAdd(&opt,"pf",'t',&pnamestr);
  OptionAdd(&opt,"if",'t',&pidstr);
  OptionAdd(&opt,"f",'x',&sfilter); /* allow stream filtering */
 
  arg=OptionProcess(1,argc,argv,&opt,NULL);   

  if (help==1) {
    OptionPrintInfo(stdout,hlpstr);
    exit(0);
  }
  if (option==1) {
    OptionDump(stdout,&opt);
    exit(0);
  }


  if (argc-arg<2) {
     OptionPrintInfo(stdout,errstr);
     exit(-1);
  }

  if (logstr !=NULL) strcpy(logfname,logstr);
  if (timestr !=NULL) strcpy(timefname,timestr);
  if (pnamestr !=NULL) strcpy(pname,pnamestr);
  if (pidstr !=NULL) strcpy(pidname,pidstr);
 
  for (c=arg;c<argc;c+=2) {
    strcpy(host[num],argv[c]);
    remoteport[num]=atoi(argv[c+1]);
    sock[num]=-1;
    num++;
  }

  sigemptyset(&set);
  sigaddset(&set,SIGPIPE);
 
  act.sa_flags=0;
  act.sa_mask=set;
  act.sa_handler=trappipe;
  sigaction(SIGPIPE,&act,NULL);

  signal(SIGCHLD,SIG_IGN); 
 
  outpipe=forkinet(port);

  do {
    for (c=0;c<num;c++) {
      if (time(NULL) > tick[c]) {
	 if (sock[c] !=-1) {
	   sprintf(logbuf,
                   "Connection to Host %s:%d timed out - connection reset",
                   host[c],remoteport[c]);
           loginfo(logfname,logbuf);
           close(sock[c]);
           sock[c]=-1;
	 }
         sprintf(logbuf,"Connecting to Host %s:%d.",host[c],remoteport[c]);
         loginfo(logfname,logbuf);
         tmout.tv_sec=timeout;
         tmout.tv_usec=0;
         sock[c]=ConnexOpen(host[c],remoteport[c],&tmout);
         if (sock[c]==-1) {
           sprintf(logbuf,"Could not connect to Host %s:%d.",
		 host[c],remoteport[c]);
           loginfo(logfname,logbuf);
	 }
         tick[c]=time(NULL)+timeout;
      }
    }

  
    cnt=0;
    for (c=0;c<num;c++) if (sock[c] !=-1) cnt++;
    if (cnt==0) {
      sleep(1);
      continue;
    }

    if (vb) {

      sprintf(logbuf,"Polling for incoming data. (%d open connections)",
	      cnt);
      loginfo(logfname,logbuf);
    }

    tmout.tv_sec=timeout;
    tmout.tv_usec=0;
    status=ConnexRead(num,sock,buffer,size,flag,&tmout);
    if (status==0) {
      loginfo(logfname,"select() timed out - restarting connections.");
      for (c=0;c<num;c++) {
        close(sock[c]);
	sock[c]=-1;
        tick[c]=time(NULL)+timeout;
      }
      continue;
    }


    if (status==-1) {
      loginfo(logfname,"select() failed - restarting connections.");
      for (c=0;c<num;c++) {
        close(sock[c]);
	sock[c]=-1;
        tick[c]=time(NULL)+timeout;
      }
      continue;
    }

    for (c=0;c<num;c++) {
      if (flag[c]==0) continue;
      if (flag[c]==-1) {
        if (vb) {
          sprintf(logbuf,"Connection to Host %s:%d failed.",
	  host[c],remoteport[c]);
          loginfo(logfname,logbuf);
	}
        close(sock[c]);
	sock[c]=-1;
        tick[c]=time(NULL)+timeout;
        continue;
      }  
      if ((outpipe==-1) && (time(NULL) > pipewait)) {
        loginfo(logfname,"Child process died - Restarting.");
        outpipe=forkinet(port);
        if (outpipe==-1) {
          pipewait=time(NULL)+timeout;
          continue;
	}
      }
      tick[c]=time(NULL)+timeout;
      if (sfilter) st=c+1;
      else st=255;
      if (vb) {
         sprintf(logbuf,"Received %d bytes from Host %s:%d.",
	         size[c],host[c],remoteport[c]);
         loginfo(logfname,logbuf);
      }
      if (outpipe==-1) continue;
      
      status=pipewrite(outpipe,st,buffer[c],size[c]);
      if (status==-1) {
            loginfo(logfname,"Pipe broken");
	    close(outpipe);
            pipewait=time(NULL)+timeout;
            outpipe=-1;
      }
    }
  } while (1);
  return 0;
}


   

 






















