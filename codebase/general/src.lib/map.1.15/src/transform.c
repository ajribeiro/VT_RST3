/* transform.c
   ===========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#ifndef _DARWIN
#include <malloc.h>
#endif
#include <math.h>
#include "rfbuffer.h"
#include "iplot.h"
#include "polygon.h"
#include "rmap.h"

#define FSTEP 0.05

struct PolygonData *MapTransform(struct PolygonData *src,
                                     int sze,
				     int (*bbox)(void *x,
						void *y,int s),
                                     int (*trf)(int ssze,void *src,int dsze,
                                                void *dst,void *data),
                                     void *data) {

  int flg,iflg;
  void *spnt,*p1,*p2;
  char *dpnt,*ipnt;
  int n,s;
  int i,j;
  int oj,fj;
  double f;

  struct PolygonData *dst=NULL;

  if (src==NULL) return NULL;
  if (trf==NULL) return NULL;

  dpnt=malloc(sze);
  ipnt=malloc(src->sze);
  if (dpnt==NULL) return NULL;
  dst=PolygonMake(sze,bbox);
  if (dst==NULL) {
    free(dpnt);
    return NULL;
  }
  
  for (i=0;i<src->polnum;i++) {    
    flg=1;
    n=src->num[i];
    oj=-1;
    fj=-1;
    iflg=0;
    for (j=0;j<n;j++) {
      spnt=PolygonRead(src,i,j);
      s=(*trf)(src->sze,spnt,sze,dpnt,data);
      if (s !=0) {
        iflg=1;       
        continue;
      }
      if (flg==1) {
        s=PolygonAddPolygon(dst,src->type[i]);
        if (s !=0) break;
        flg=0;
        fj=j;
      }
      
      if ((oj !=-1) && (iflg==1)) { /* fill in missing segment */
        p1=PolygonRead(src,i,oj);
        p2=PolygonRead(src,i,j);
        for (f=0;f<1;f+=FSTEP) {
          MapGreatCircle(p1,p2,f,ipnt);
          s=(*trf)(src->sze,ipnt,sze,dpnt,data);
          if (s==0) {
            s=PolygonAdd(dst,dpnt);
            if (s !=0) break;
	  }
        }
      }

      oj=j;
      s=PolygonAdd(dst,dpnt);
      if (s !=0) break;
    }

    if ((flg==0) && (iflg==1)) { /* close segment */

      p1=PolygonRead(src,i,oj);
      p2=PolygonRead(src,i,fj);
      for (f=0;f<1;f+=FSTEP) {
        MapGreatCircle(p1,p2,f,ipnt);
        s=(*trf)(src->sze,ipnt,sze,dpnt,data);
        if (s==0) {
          s=PolygonAdd(dst,dpnt);
          if (s !=0) break;
	}
      }
    }


    if (j !=n) break;
  }
  free(ipnt);
  free(dpnt);
  if (i !=src->polnum) {
    PolygonFree(dst);
    return NULL;
  } 
  return dst;
}


void MapModify(struct PolygonData *src,
                   int (*trf)(int ssze,void *src,int dsze,
                              void *dst,void *data),void *data) {

  int flg;
  void *pnt;
  int n,s;
  int i,j;
  if (src==NULL) return;
  if (trf==NULL) return;
 
  for (i=0;i<src->polnum;i++) {    
    flg=1;
    n=src->num[i];       
    for (j=0;j<n;j++) {
      pnt=PolygonRead(src,i,j);
      s=(*trf)(src->sze,pnt,src->sze,pnt,data);
    }
  }
}


