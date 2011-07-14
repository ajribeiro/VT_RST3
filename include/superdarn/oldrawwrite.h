/* oldrawwrite.h
   =============
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#ifndef _OLDRAWWRITE_H
#define _OLDRAWWRITE_H

int OldRawWrite(int fid,char *name,struct RadarParm *prm,
                struct RawData *raw,int recnum,int *rtab);

int OldRawHeaderWrite(int fid,char *name,char *version,
                     int thr,char *text);

int OldRawFwrite(FILE *fp,char *name,struct RadarParm *prm,
                struct RawData *raw,int recnum,int *rtab);

int OldRawHeaderFwrite(FILE *fp,char *name,char *version,
                     int thr,char *text);

#endif












