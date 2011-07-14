/* site.c
   ====== 
   Author R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include "rtypes.h"
#include "limit.h"
#include "tsg.h"
#include "maketsg.h"
#include "acf.h"
#include "acfex.h"
#include "tcpipmsg.h"
#include "rosmsg.h"
#include "shmem.h"
#include "global.h"
#include "site.h"
#include "siteglobal.h"

#define REAL_BUF_OFFSET 0
#define IMAG_BUF_OFFSET 1

#define USEC 1000000.0

void SiteTstExit(int signum) {

  struct ROSMsg msg;
  
  if (signum==13) errno=EPIPE;
  else {
    msg.type=QUIT;
    TCPIPMsgSend(sock, &msg, sizeof(struct ROSMsg));
    TCPIPMsgRecv(sock, &msg, sizeof(struct ROSMsg));
    if (debug) {
      fprintf(stderr,"QUIT:type=%c\n",msg.type);
      fprintf(stderr,"QUIT:status=%d\n",msg.status);
    }

    close(sock);
   
  }
  if (samples !=NULL)
    ShMemFree((unsigned char *) samples,sharedmemory,IQBUFSIZE,1,shmemfd);

  exit(errno);    
}



int SiteTstStart() {
  signal(SIGPIPE,SiteTstExit);
  signal(SIGINT,SiteTstExit);
  signal(SIGUSR1,SiteTstExit);

  sock=0;
  strcpy(server,"127.0.0.1");
  port=45000;
  rnum=1;
  
  return 0;
}


int SiteTstSetupRadar() {

  struct ROSMsg smsg,rmsg;

  if ((sock=TCPIPMsgOpen(server,port)) == -1) {
    return -1;
  }

  smsg.type=SET_RADAR_CHAN;
  TCPIPMsgSend(sock, &smsg,sizeof(struct ROSMsg)); 
  TCPIPMsgSend(sock, &rnum, sizeof(int)); 
  TCPIPMsgSend(sock, &cnum, sizeof(int));
  TCPIPMsgRecv(sock, &rmsg, sizeof(struct ROSMsg)); 

  if (debug) {
    fprintf(stderr,"SET_RADAR_CHAN:type=%c\n",rmsg.type);
    fprintf(stderr,"SET_RADAR_CHAN:status=%d\n",rmsg.status);
  }

  smsg.type=GET_PARAMETERS;
  TCPIPMsgSend(sock, &smsg, sizeof(struct ROSMsg));
  TCPIPMsgRecv(sock, &rprm, sizeof(struct ControlPRM));
  TCPIPMsgRecv(sock, &rmsg, sizeof(struct ROSMsg));

  if (debug) {
    fprintf(stderr,"GET_PARAMETERS:type=%c\n",rmsg.type);
    fprintf(stderr,"GET_PARAMETERS:status=%d\n",rmsg.status);
  
  }

  strcpy(sharedmemory,"IQBuffertst");

  samples=(int16 *)
    ShMemAlloc(sharedmemory,IQBUFSIZE,O_RDWR | O_CREAT,1,&shmemfd);

  return 0;
}

 
int SiteTstStartScan() {
  return 0;
}



int SiteTstStartIntt(int sec,int usec) {

  struct ROSMsg smsg,rmsg;
  
  smsg.type=PING; 
  TCPIPMsgSend(sock, &smsg, sizeof(struct ROSMsg));
  TCPIPMsgRecv(sock, &rmsg, sizeof(struct ROSMsg));

  if (debug) {
    fprintf(stderr,"PING:type=%c\n",rmsg.type);
    fprintf(stderr,"PING:status=%d\n",rmsg.status);
  }

  smsg.type=GET_PARAMETERS;
  TCPIPMsgSend(sock, &smsg, sizeof(struct ROSMsg));
  TCPIPMsgRecv(sock, &rprm, sizeof(struct ControlPRM));
  TCPIPMsgRecv(sock, &rmsg, sizeof(struct ROSMsg));
     
  if (debug) {
    fprintf(stderr,"GET_PARAMETERS:type=%c\n",rmsg.type);
    fprintf(stderr,"GET_PARAMETERS:status=%d\n",rmsg.status);

  }

  rprm.tbeam=bmnum;   
  rprm.tfreq=12000;   
  rprm.trise=5000;   
  rprm.baseband_samplerate=((double)nbaud/(double)txpl)*1E6; 
  rprm.filter_bandwidth=rprm.baseband_samplerate; 
  rprm.match_filter=1;
  rprm.number_of_samples=tsgprm.samples; 

  smsg.type=SET_PARAMETERS;
  TCPIPMsgSend(sock,&smsg,sizeof(struct ROSMsg));
  TCPIPMsgSend(sock,&rprm,sizeof(struct ControlPRM));
  TCPIPMsgRecv(sock,&rmsg,sizeof(struct ROSMsg));

  if (debug) {
    fprintf(stderr,"SET_PARAMETERS:type=%c\n",rmsg.type);
    fprintf(stderr,"SET_PARAMETERS:status=%d\n",rmsg.status);
  }

  if (gettimeofday(&tock,NULL)==-1) return -1;
  tock.tv_sec+=sec;
  tock.tv_usec+=usec;

  rxchn=2;

  return 0;


}


int SiteTstFCLR(int stfreq,int edfreq) {
  int tfreq;
  struct ROSMsg smsg,rmsg;
  struct CLRFreqPRM fprm;

  fprm.start=stfreq; 
  fprm.end=edfreq;  
  fprm.nave=20;  
  fprm.filter_bandwidth=250;  

  smsg.type=REQUEST_CLEAR_FREQ_SEARCH;
  TCPIPMsgSend(sock, &smsg, sizeof(struct ROSMsg));
  TCPIPMsgSend(sock, &fprm, sizeof(struct CLRFreqPRM));
  TCPIPMsgRecv(sock, &rmsg, sizeof(struct ROSMsg));

  if (debug) {
    fprintf(stderr,"REQUEST_CLEAR_FREQ_SEARCH:type=%c\n",rmsg.type);
    fprintf(stderr,"REQUEST_CLEAR_FREQ_SEARCH:status=%d\n",rmsg.status);
 
  }
  smsg.type=REQUEST_ASSIGNED_FREQ;
  TCPIPMsgSend(sock, &smsg, sizeof(struct ROSMsg));
  TCPIPMsgRecv(sock,&tfreq, sizeof(int)); 
  TCPIPMsgRecv(sock,&noise, sizeof(float));  
  TCPIPMsgRecv(sock,&rmsg, sizeof(struct ROSMsg)); 

  if (debug) {
    fprintf(stderr,"REQUEST_ASSIGNED_FREQ:type=%c\n",rmsg.status);
    fprintf(stderr,"REQUEST_ASSIGNED_FREQ:status=%d\n",rmsg.status);
  }

  return tfreq;
}



int SiteTstTimeSeq(int *ptab) {

  int i;
  int flag,index=0;
  struct ROSMsg smsg,rmsg;

  struct TSGPRM tprm;

  if (tsgbuf !=NULL) TSGFree(tsgbuf);
  if (tsgprm.pat !=NULL) free(tsgprm.pat);
  memset(&tsgprm,0,sizeof(struct TSGprm));

  tsgprm.nrang=nrang;         
  tsgprm.frang=frang;
  tsgprm.rtoxmin=360;      
  tsgprm.stdelay=18+2;
  tsgprm.gort=1;
  tsgprm.rsep=rsep;          
  tsgprm.smsep=smsep;
  tsgprm.txpl=txpl; 
  tsgprm.mpinc=mpinc;
  tsgprm.mppul=mppul; 
  tsgprm.mlag=0;
  tsgprm.nbaud=nbaud;
  tsgprm.code=pcode;
  tsgprm.pat=malloc(sizeof(int)*tsgprm.mppul);
  for (i=0;i<tsgprm.mppul;i++) tsgprm.pat[i]=ptab[i];

  tsgbuf=TSGMake(&tsgprm,&flag);

  if (tsgbuf==NULL) return -1;

  tprm.index=index;
  memcpy(&tprm.buf,tsgbuf,sizeof(struct TSGbuf));
  tprm.step=CLOCK_PERIOD;
  tprm.prm=&tsgprm;


  smsg.type=REGISTER_SEQ;
  TCPIPMsgSend(sock, &smsg, sizeof(struct ROSMsg));

  TCPIPMsgSend(sock, &index, sizeof(index));
  TCPIPMsgSend(sock, &tprm, sizeof(struct TSGPRM));
  TCPIPMsgSend(sock, tsgbuf->rep, sizeof(unsigned char)*tsgbuf->len);
  TCPIPMsgSend(sock, tsgbuf->code, sizeof(unsigned char)*tsgbuf->len);
  TCPIPMsgSend(sock, &tsgprm, sizeof(struct TSGprm));
  TCPIPMsgRecv(sock, &rmsg, sizeof(struct ROSMsg));

  if (debug) {
    fprintf(stderr,"REGISTER_SEQ:type=%c\n",rmsg.type);
    fprintf(stderr,"REGISTER_SEQ:status=%d\n",rmsg.status);
  }

  if (rmsg.status !=1) return -1;

  lagfr=tsgprm.lagfr;
  smsep=tsgprm.smsep;
  txpl=tsgprm.txpl;

  return index;
}

int SiteTstIntegrate(int (*lags)[2]) {

  int *lagtable[2]={NULL,NULL};
  int lagsum[LAG_SIZE];

  int badrng=0;
  int i=0,j,range,lag;
  int roff=REAL_BUF_OFFSET;
  int ioff=IMAG_BUF_OFFSET;

  struct timeval tick;
  struct timeval tack;

  double tval=0,tavg=0;

  struct ROSMsg smsg,rmsg;

  int iqoff=0;
  int iqsze=0;

  int nave=0;

  int atstp=0;
  int thr=0,lmt=0;
  int aflg=0,abflg=0;

  for (j=0;j<LAG_SIZE;j++) lagsum[j]=0;

  if (mplgexs==0) {
    lagtable[0]=malloc(sizeof(int)*(mplgs+1));
    lagtable[1]=malloc(sizeof(int)*(mplgs+1));

    for (i=0;i<=mplgs;i++) {
      lagtable[0][i]=lags[i][0];
      lagtable[1][i]=lags[i][1];
    }
  } else {
    lagtable[0]=malloc(sizeof(int)*(mplgexs+1));
    lagtable[1]=malloc(sizeof(int)*(mplgexs+1));

    for (i=0;i<=mplgexs;i++) {
      lagtable[0][i]=lags[i][0];
      lagtable[1][i]=lags[i][1];
      j=abs(lags[i][0]-lags[i][1]);
      lagsum[j]++;
    }
  }


  rxchn=2;
  smpnum=tsgprm.samples+tsgprm.smdelay-1;
  skpnum=tsgprm.smdelay;

  badrng=ACFBadLagZero(&tsgprm,mplgs,lagtable);

  gettimeofday(&tick,NULL);
  gettimeofday(&tack,NULL);

    for (i=0;i<MAX_RANGE;i++) {
      pwr0[i]=0;
      for (j=0;j<LAG_SIZE*2;j++) {
        acfd[i*LAG_SIZE*2+j]=0;
        xcfd[i*LAG_SIZE*2+j]=0;
      }
    }

  while (1) {
     
    seqtval[nave].tv_sec=tick.tv_sec;
    seqtval[nave].tv_nsec=tick.tv_usec*1000;
    seqatten[nave]=0;
    seqnoise[nave]=0;

    seqbadtr[nave].num=0;
    if (seqbadtr[nave].start !=NULL) free(seqbadtr[nave].start);
    if (seqbadtr[nave].length !=NULL) free(seqbadtr[nave].length);
    seqbadtr[nave].start=NULL;
    seqbadtr[nave].length=NULL;
  

    tval=(tick.tv_sec+tick.tv_usec/1.0e6)-
         (tack.tv_sec+tack.tv_usec/1.0e6);

    if (nave>0) tavg=tval/nave; 
     
    tick.tv_sec+=floor(tavg);
    tick.tv_usec+=1.0e6*(tavg-floor(tavg));

    if (tick.tv_sec>tock.tv_sec) break;
    if ((tick.tv_sec>=tock.tv_sec) && (tick.tv_usec>tock.tv_usec)) break;

    rprm.tbeam=bmnum;   
    rprm.tfreq=tfreq;   
    rprm.rfreq=tfreq;   
    rprm.trise=5000;   
    rprm.baseband_samplerate=((double)nbaud/(double)txpl)*1E6; 
    rprm.filter_bandwidth=rprm.baseband_samplerate; 
    rprm.match_filter=1;
    rprm.number_of_samples=tsgprm.samples; 

    smsg.type=SET_PARAMETERS;
    TCPIPMsgSend(sock,&smsg,sizeof(struct ROSMsg));
    TCPIPMsgSend(sock,&rprm,sizeof(struct ControlPRM));
    TCPIPMsgRecv(sock,&rmsg,sizeof(struct ROSMsg));

    if (debug) {
      fprintf(stderr,"SET_PARAMETERS:type=%c\n",rmsg.type);
      fprintf(stderr,"SET_PARAMETERS:status=%d\n",rmsg.status);
    }

    smsg.type=SET_READY_FLAG;
    TCPIPMsgSend(sock,&smsg,sizeof(struct ROSMsg));
    TCPIPMsgRecv(sock,&rmsg,sizeof(struct ROSMsg));

    if (debug) {
      fprintf(stderr,"SET_READY_FLAG:type=%c\n",rmsg.type);
      fprintf(stderr,"SET_READY_FLAG:status=%d\n",rmsg.status);
    }

    smsg.type=GET_DATA;
    TCPIPMsgSend(sock,&smsg,sizeof(struct ROSMsg));

    if (rdata.main!=NULL) free(rdata.main);
    if (rdata.back!=NULL) free(rdata.back);

    TCPIPMsgRecv(sock,&rdata,sizeof(struct ControlData));

    rdata.main=malloc(4*rdata.samples);
    rdata.back=malloc(4*rdata.samples);
    TCPIPMsgRecv(sock, rdata.main, 4*rdata.samples);
    TCPIPMsgRecv(sock, rdata.back, 4*rdata.samples);

    if (badtrdat.start_usec !=NULL) free(badtrdat.start_usec);
    if (badtrdat.duration_usec !=NULL) free(badtrdat.duration_usec);

    TCPIPMsgRecv(sock, &badtrdat, sizeof(struct BadTR));

    badtrdat.start_usec=malloc(sizeof(unsigned int)*badtrdat.length);
    badtrdat.duration_usec=malloc(sizeof(unsigned int)*badtrdat.length);

    TCPIPMsgRecv(sock, badtrdat.start_usec,
                 sizeof(unsigned int)*badtrdat.length);
    TCPIPMsgRecv(sock, badtrdat.duration_usec,
                 sizeof(unsigned int)*badtrdat.length);

    TCPIPMsgRecv(sock, &num_transmitters, sizeof(int));
    TCPIPMsgRecv(sock, &txstatus.AGC, sizeof(int)*num_transmitters);
    TCPIPMsgRecv(sock, &txstatus.LOWPWR, sizeof(int)*num_transmitters);

    TCPIPMsgRecv(sock, &rmsg, sizeof(struct ROSMsg));

    if (debug) {
      fprintf(stderr,"GET_DATA:type=%c\n",rmsg.type);
      fprintf(stderr,"GET_DATA:status=%d\n",rmsg.status);

    }

    smsg.type=GET_PARAMETERS;
    TCPIPMsgSend(sock, &smsg, sizeof(struct ROSMsg));
    TCPIPMsgRecv(sock, &rprm, sizeof(struct ControlPRM));
    TCPIPMsgRecv(sock, &rmsg, sizeof(struct ROSMsg));
     
    if (debug) {
      fprintf(stderr,"GET_PARAMETERS:type=%c\n",rmsg.type);
      fprintf(stderr,"GET_PARAMETERS:status=%d\n",rmsg.status);
      fprintf(stderr,"Number of samples=%d %d\n",rdata.samples,tsgprm.samples);
      fprintf(stderr,"nave=%d\n",nave);
    }

    /* copy samples here */

    seqoff[nave]=iqsze/2;
    seqsze[nave]=rdata.samples*4;

    seqbadtr[nave].num=badtrdat.length;
    seqbadtr[nave].start=malloc(sizeof(unsigned int)*badtrdat.length);
    seqbadtr[nave].length=malloc(sizeof(unsigned int)*badtrdat.length);

    memcpy(seqbadtr[nave].start,badtrdat.start_usec,
           sizeof(unsigned int)*badtrdat.length);
    memcpy(seqbadtr[nave].length,badtrdat.duration_usec,
           sizeof(unsigned int)*badtrdat.length);

    memcpy(samples+iqoff,rdata.main,rdata.samples*4);
    memcpy(samples+iqoff+rdata.samples*4,rdata.back,rdata.samples*4);
    

    iqsze+=rdata.samples*4*2;
    iqoff=iqsze;

    /* calculate ACF */   
    if (mplgexs==0) {
      aflg=ACFSumPower(&tsgprm,mplgs,lagtable,pwr0,
	    	       (int16 *) rdata.main,2,1,
                       roff,ioff,badrng,
                       noise,mxpwr,atten*atstp,
                       thr,lmt,&abflg);
       
      ACFCalculate(&tsgprm,(int16 *) rdata.main,2,1,
                   roff,ioff,mplgs,
	    	   lagtable,acfd,ACF_PART,2,badrng,atten*atstp,NULL);
    }
    nave++;
    gettimeofday(&tick,NULL);
  }

  /* Now divide by nave to get the average pwr0 and acfd values for the 
     integration period */
  if (mplgexs==0) {
    if (nave > 0 ) {
      for(range=0; range < nrang;range++) {
        pwr0[range]=(double)pwr0[range]/(double)nave;
 
        for(lag=0;lag < mplgs; lag++) {     
           acfd[range*(2*mplgs)+2*lag]= (double) acfd[range*(2*mplgs)+2*lag]/
                                        (double) nave;
        }
      }
    }
  } else if (nave>0) {
    /* ACFEX calculation */
    ACFexCalculate(&tsgprm,(int16 *) samples,nave*smpnum,nave,smpnum,
                   roff,ioff,
		   mplgs,mplgexs,lagtable,lagsum,
		   pwr0,acfd,&noise);
  
  }

  free(lagtable[0]);
  free(lagtable[1]);
  return nave;
}

int SiteTstEndScan(int bsc,int bus) {

  struct ROSMsg smsg,rmsg;
  smsg.type=PING;
  
  struct timeval tock;
  struct timeval tick;
  double bnd;
  double tme;

  bnd=bsc+bus/USEC;

  if (gettimeofday(&tock,NULL)==-1) return -1;

  tme=tock.tv_sec+tock.tv_usec/USEC;
  tme=bnd*floor(1.0+tme/bnd);
  tock.tv_sec=tme;
  tock.tv_usec=(tme-floor(tme))*USEC;

  gettimeofday(&tick,NULL);

  while (1) {
    if (tick.tv_sec>tock.tv_sec) break;
    if ((tick.tv_sec==tock.tv_sec) && (tick.tv_usec>tock.tv_usec)) break;
    usleep(50000);

    TCPIPMsgSend(sock, &smsg, sizeof(struct ROSMsg));
    TCPIPMsgRecv(sock, &rmsg, sizeof(struct ROSMsg));

    if (debug) {
      fprintf(stderr,"PING:type=%c\n",rmsg.type);
      fprintf(stderr,"PING:status=%d\n",rmsg.status);
    }

    gettimeofday(&tick,NULL);
  }

  return 0;
}







