/* oldgridread.h
   =============
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#ifndef _OLDGRIDREAD_H
#define _OLDGRIDREAD_H

int OldGridDecodeOne(char *name,char *unit,char *type,
                    double st_time,double ed_time,
                    int npnt,int nprm,int pnt,
                    struct RfileData *data,void *ptr);

int OldGridDecodeTwo(char *name,char *unit,char *type,
                    double st_time,double ed_time,
                    int npnt,int nprm,int pnt,
                    struct RfileData *data,void *ptr);

int OldGridDecodeThree(char *name,char *unit,char *type,
                    double st_time,double ed_time,
                    int npnt,int nprm,int pnt,
                    struct RfileData *data,void *ptr);

int OldGridDecodeFour(char *name,char *unit,char *type,
                    double st_time,double ed_time,
                    int npnt,int nprm,int pnt,
                    struct RfileData *data,void *ptr);

int OldGridDecodeFive(char *name,char *unit,char *type,
                    double st_time,double ed_time,
                    int npnt,int nprm,int pnt,
                    struct RfileData *data,void *ptr);

int OldGridDecodeSix(char *name,char *unit,char *type,
                    double st_time,double ed_time,
                    int npnt,int nprm,int pnt,
                    struct RfileData *data,void *ptr);


int OldGridFread(FILE *fp,struct GridData *);

int OldGridFseek(FILE *fp,
	         int yr,int mo,int dy,int hr,int mt,int sc,
                 struct RfileIndex *inx,
                 double *aval);
#endif
