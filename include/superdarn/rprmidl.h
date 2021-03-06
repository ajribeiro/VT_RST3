/* rprmidl.h
   =========
   Author R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.



*/

#ifndef _RPRMIDL_H
#define _RPRMIDL_H

#define PULSE_SIZE 64
#define LAG_SIZE 96
#define MAX_RANGE 300

#define ORIGIN_TIME_SIZE 26
#define ORIGIN_COMMAND_SIZE 128
#define COMBF_SIZE 80



struct RadarIDLParm
{
  struct
  {
    UCHAR major;
    UCHAR minor;
  } revision;

  struct
  {
    UCHAR code;
    IDL_STRING time;
    IDL_STRING command;
  } origin;


  short cp;
  short stid;

  struct
  {
    short yr;
    short mo;
    short dy;
    short hr;
    short mt;
    short sc;
    IDL_LONG us;
  } time;

  short txpow;
  short nave;
  short atten;
  short lagfr;
  short smsep;
  short  ercod;

  struct
  {
    short agc;
    short lopwr;
  } stat;

  struct
  {
    float search;
    float mean;
  } noise;

  short channel;
  short bmnum;
  float bmazm;
  short scan;

  short rxrise;
  struct
  {
    short sc;
    IDL_LONG us;
  } intt;
  short txpl;
  short mpinc;
  short mppul;
  short mplgs;
  short mplgexs;
  /* Lasse Clausen's edit, to include the ifmode parameter*/
  short ifmode;
  short nrang;
  short frang;
  short rsep;
  short xcf;
  short tfreq;
  short offset;

  IDL_LONG mxpwr;
  IDL_LONG lvmax;

  short pulse[PULSE_SIZE];
  short lag[LAG_SIZE*2];
  IDL_STRING combf;
};


struct RadarIDLParm *IDLMakeRadarParm( IDL_VPTR *vptr );

void IDLCopyRadarParmToIDL( struct RadarParm *prm,
                            struct RadarIDLParm *iprm );

void IDLCopyRadarParmFromIDL( struct RadarIDLParm *iprm, struct RadarParm *prm );


#endif
