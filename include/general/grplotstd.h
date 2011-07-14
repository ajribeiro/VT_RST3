/* grplotstd.h
   ===========
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#ifndef _GRPLOTSTD_H
#define _GRPLOTSTD_H

int GrplotStdKey(struct Plot *ptr,
               float ox,float oy,float wdt,float hgt,
               double min,double max,double step,
               int or,int txt_or,int tflg,
               int ttl_num,char *ttl_text,
               int  (*text_box)(char *,float,int,char *,float *,void *),
               void *boxdata,
               char * (*make_text)(double,double,double,void *),
               void *textdata,
               char *fntname,float fntsze,
               unsigned int color,unsigned char mask,float width,
               int ksze,unsigned char *a,
               unsigned char *r,unsigned char *g,unsigned char *b);

int GrplotStdKeyLog(struct Plot *ptr,
               float ox,float oy,float wdt,float hgt,
	       double min,double max,double tick_major,double tick_minor,
	       int or,int txt_or,int tflg, 
               int ttl_num,char *ttl_text,
	       int  (*text_box)(char *,float,int,char *,float *,void *),
               void *boxdata,
               char * (*make_text)(double,double,double,void *),
               void *textdata,
               char *fntname,float fntsze,
               unsigned int color,unsigned char mask,float width,
	       int ksze,unsigned char *a,
               unsigned char *r,unsigned char *g,unsigned char *b);


#endif
