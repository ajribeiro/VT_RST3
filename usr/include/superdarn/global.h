/* global.h
   ======== 
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/


#ifndef _GLOBAL_H
#define _GLOBAL_H

extern struct RadarParm *prm;
extern struct IQ *iq;
extern struct RawData *raw;
extern struct FitData *fit;
extern struct FitBlock *fblk;
extern struct RadarSite *site;
extern struct FreqTable *ftable;
extern struct RShellTable rstable;
extern struct RadarNetwork *network;
extern struct Radar *radar;

extern struct TSGbuf *tsgbuf;
extern struct TSGprm tsgprm;

extern struct RMsgBlock msg;

extern struct RShellTable rstable;

extern unsigned char command[128];

extern int debug;


extern int rnum;
extern int cnum;

extern int maxatten;
extern int protatten;

extern int tsgid;
extern int stid;
extern int yr;
extern int mo;
extern int dy;
extern int hr;
extern int mt;
extern int sc;
extern int us;
extern int txpow;
extern int nave;
extern int atten;
extern int lagfr;
extern int smsep;
extern int ercod;
extern int agcstat;
extern int lopwrstat;
extern int nbaud;
extern float noise;
extern int rxrise;
extern int intsc;
extern int intus;
extern int txpl;
extern int mpinc;
extern int mppul;
extern int mplgs;
extern int mplgexs;
extern int nrang;
extern int frang;
extern int rsep;
extern int bmnum;
extern int xcf;
extern int tfreq;
extern int scan;
extern int mxpwr;
extern int lvmax;
extern int cp;

extern int *pcode;

extern int noisefac;
extern int noiselim;

extern float noisestat[4];
extern char combf[128];

extern int rxchn;
extern int smpnum;
extern int skpnum;
extern struct timespec seqtval[MAXNAVE];
extern int seqatten[MAXNAVE];
extern float seqnoise[MAXNAVE];
extern int seqoff[MAXNAVE];
extern int seqsze[MAXNAVE];

extern struct {
  int num;
  unsigned int *start;
  unsigned int *length;
} seqbadtr[MAXNAVE];

extern int16 *samples;

extern unsigned int *badtr;

extern int shmemfd;
extern char sharedmemory[256];

extern float pwr0[MAX_RANGE];
extern float acfd[MAX_RANGE*LAG_SIZE*2];
extern float xcfd[MAX_RANGE*LAG_SIZE*2];

extern int backward;
extern int sbm;
extern int ebm;

extern int xcnt;

extern int day;
extern int night;

extern int dfrq;
extern int nfrq;

extern int dmpinc;
extern int nmpinc;

extern int dfrang;
extern int nfrang;

extern int stfrq;
extern int frqrng;



#endif












