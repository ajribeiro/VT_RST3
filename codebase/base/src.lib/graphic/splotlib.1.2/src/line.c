/* line.c
   ====== 
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rfbuffer.h"
#include "fontdb.h"
#include "rps.h"
#include "iplot.h"
#include "splot.h"

int SplotLine(struct Splot *ptr,
              float ax,float ay,float bx,float by,
              unsigned int color,unsigned char mask,float width,
              struct PlotDash *dash) {
  
  if (ptr==NULL) return -1;
  if (ptr->ps.ptr !=NULL) {
    unsigned int pscolor;      
    SplotPostScriptDash(ptr,dash);
    pscolor=SplotPostScriptColor(color);
    return PostScriptLine(ptr->ps.ptr,ax,ay,bx,by,pscolor,
                          width,ptr->ps.dash,ptr->ps.clip);
  } 


  if (ptr->fb.ptr !=NULL) {
    struct FrameBuffer *img;
    img=*(ptr->fb.ptr);
    if (img==NULL) return -1;
    SplotFrameBufferDash(ptr,dash);
    return FrameBufferLine(img,ax,ay,bx,by,color,mask,
                          width,ptr->fb.dash,ptr->fb.clip);
  }
  return 0;

} 



