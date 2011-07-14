/* grplotraw_key.c
   ===============
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "rfbuffer.h"
#include "iplot.h"
#include "polygon.h"
#include "grplotraw.h"



int GrplotRawKey(struct Plot *ptr,
               float ox,float oy,float wdt,float hgt,
	       double min,double max,
     	       double tick_major,double tick_minor,
               float major_size,float minor_size,
               float txt_off,float ttl_off,
               int tick_flg,int txt_flg,int ttl_flg,
               int txt_or,int ttl_or,
               int or, 
               int ttl_num,char *ttl_text,
	       int  (*text_box)(char *,float,int,char *,float *,void *),
               void *boxdata,
               char * (*make_text)(double,double,double,void *),
               void *textdata,
               char *fntname,float fntsze,
               unsigned int color,unsigned char mask,float width,
               int ksze,unsigned char *a,
               unsigned char *r,unsigned char *g,unsigned char *b) {
  int s=0;
  int i=0;
  struct FrameBuffer *img=NULL;

  if (ptr==NULL) return -1;
  if (text_box==NULL) return -1;
  if (fntname==NULL) return -1;
  if (fntsze==0) return -1;
  if (ksze==0) return -1;
  

  if (or==0) img=FrameBufferMake(NULL,1,ksze,24);
  else img=FrameBufferMake(NULL,ksze,1,24);

  if (img==NULL) return -1;

  if (or==0) {
    for (i=0;i<ksze;i++) {
      if (a !=NULL) img->msk[ksze-1-i]=a[i];
      if (r !=NULL) img->img[ksze-1-i]=r[i];
      if (g !=NULL) img->img[2*ksze-1-i]=g[i];
      if (b !=NULL) img->img[3*ksze-1-i]=b[i];
    }
  } else {
    for (i=0;i<ksze;i++) {
      if (a !=NULL) img->msk[i]=a[i];
      if (r !=NULL) img->img[i]=r[i];
      if (g !=NULL) img->img[ksze+i]=g[i];
      if (b !=NULL) img->img[2*ksze+i]=b[i];
    }
  }


  s=GrplotRawFitImage(ptr,ox,oy,wdt,hgt,img,mask);
  
  if (s==0) s=GrplotRawPanel(ptr,ox,oy,wdt,hgt,color,mask,width);
  if (or==0) {
    if (s==0) s=GrplotRawYaxis(ptr,ox,oy,wdt,hgt,
                 min,max,tick_major,tick_minor,major_size,minor_size,
                 tick_flg,color,mask,width);
    if ((s==0) && (make_text !=NULL)) 
         s=GrplotRawYaxisLabel(ptr,ox,oy,wdt,hgt,min,max,tick_major,txt_off,
                      txt_flg,txt_or,text_box,boxdata,
		      make_text,textdata,fntname,fntsze,color,mask);
    
  } else {
    if (s==0) s=GrplotRawXaxis(ptr,ox,oy,wdt,hgt,
                 min,max,tick_major,tick_minor,major_size,minor_size,
                 tick_flg,color,mask,width);
    if ((s==0) && (make_text !=NULL))
        s=GrplotRawXaxisLabel(ptr,ox,oy,wdt,hgt,min,max,tick_major,txt_off,
                      txt_flg,txt_or,text_box,boxdata,
                      make_text,textdata,fntname,fntsze,color,mask);
  }

  if ((s==0) && (ttl_text !=NULL) && (ttl_num !=0)) 
      s=GrplotRawYaxisTitle(ptr,ox,oy,wdt,hgt,ttl_off,ttl_flg,ttl_or,
                          text_box,boxdata,
                          ttl_num,ttl_text,fntname,fntsze,color,mask);

  FrameBufferFree(img);
  return s;
}





int GrplotRawKeyLog(struct Plot *ptr,
               float ox,float oy,float wdt,float hgt,
               double min,double max,
               double tick_major,double tick_minor,
               float major_size,float minor_size,
               float txt_off,float ttl_off,
               int tick_flg,int txt_flg,int ttl_flg,
               int txt_or,int ttl_or,
               int or,
               int ttl_num,char *ttl_text,
               int  (*text_box)(char *,float,int,char *,float *,void *),
               void *boxdata,
               char * (*make_text)(double,double,double,void *),
               void *textdata,
               char *fntname,float fntsze,
               unsigned int color,unsigned char mask,float width,
               int ksze,unsigned char *a,
               unsigned char *r,unsigned char *g,unsigned char *b) {

  int s=0;
  int i=0;
  struct FrameBuffer *img;

  if (ptr==NULL) return -1;
  if (text_box==NULL) return -1;
  if (fntname==NULL) return -1;
  if (fntsze==0) return -1;
  if (ksze==0) return -1;
  

  if (or==0) img=FrameBufferMake(NULL,1,ksze,24);
  else img=FrameBufferMake(NULL,ksze,1,24);

  if (img==NULL) return -1;

  if (or==0) {
    for (i=0;i<ksze;i++) {
      if (a !=NULL) img->msk[ksze-1-i]=a[i];
      if (r !=NULL) img->img[ksze-1-i]=r[i];
      if (g !=NULL) img->img[2*ksze-1-i]=g[i];
      if (b !=NULL) img->img[3*ksze-1-i]=b[i];
    }
  } else {
    for (i=0;i<ksze;i++) {
      if (a !=NULL) img->msk[i]=a[i];
      if (r !=NULL) img->img[i]=r[i];
      if (g !=NULL) img->img[ksze+i]=g[i];
      if (b !=NULL) img->img[2*ksze+i]=b[i];
    }
  }
 
  s=GrplotRawFitImage(ptr,ox,oy,wdt,hgt,img,mask);
 
  if (s==0) s=GrplotRawPanel(ptr,ox,oy,wdt,hgt,color,mask,width);
  if (or==0) {
    if (s==0) s=GrplotRawYaxisLog(ptr,ox,oy,wdt,hgt,
                 min,max,tick_major,tick_minor,major_size,minor_size,
                 tick_flg,color,mask,width);
    if ((s==0) && (make_text !=NULL))
       s=GrplotRawYaxisLabel(ptr,ox,oy,wdt,hgt,min,max,tick_major,txt_off,
                      txt_flg,txt_or,text_box,boxdata,
                      make_text,textdata,fntname,fntsze,color,mask);

  } else {
    if (s==0) s=GrplotRawXaxisLog(ptr,ox,oy,wdt,hgt,
                 min,max,tick_major,tick_minor,major_size,minor_size,
                 tick_flg,color,mask,width);
    if ((s==0) && (make_text !=NULL)) 
       s=GrplotRawXaxisLabel(ptr,ox,oy,wdt,hgt,min,max,tick_major,txt_off,
                      txt_flg,txt_or,text_box,boxdata,
                      make_text,textdata,fntname,fntsze,color,mask);
  }


  if ((s==0) && (ttl_text !=NULL) && (ttl_num !=0)) 
      s=GrplotRawYaxisTitle(ptr,ox,oy,wdt,hgt,ttl_off,ttl_flg,ttl_or,
                          text_box,boxdata,
                           ttl_num,ttl_text,fntname,fntsze,color,mask);
  FrameBufferFree(img);
  return s;
}







