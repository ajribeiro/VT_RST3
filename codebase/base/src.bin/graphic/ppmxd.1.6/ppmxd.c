/* xmld.c
   ====== */

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/


#ifdef _XLIB_
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "option.h"
#include "rfbuffer.h"

#include "hlpstr.h"

#ifdef _XLIB_
#include "xwin.h"
#endif



struct OptionData opt;

int main(int argc,char *argv[]) {

#ifdef _XLIB_
  char *name="ppmxd";
  int xdf=0;
  struct XwinDisplay *dp;
  struct XwinWindow *win;
  char *display_name=NULL;
  int xdoff=-1;
  int ydoff=-1;
#endif

  int arg=0;
  FILE *fp;

  unsigned int bgcolor=0;
  struct FrameBufferMatrix m;
  struct FrameBuffer *src=NULL;
  struct FrameBuffer *dst=NULL;
 
  char *bgtxt=NULL;
  unsigned char cflg=0;
  unsigned char sflg=0;
  float scale=100;

  float wdt=-1;
  float hgt=-1;
  unsigned char help=0;
  unsigned char option=0;

 
  OptionAdd(&opt,"-help",'x',&help);
  OptionAdd(&opt,"-option",'x',&option);

  OptionAdd(&opt,"smooth",'x',&sflg);
  OptionAdd(&opt,"scale",'f',&scale);
  OptionAdd(&opt,"check",'x',&cflg);
  OptionAdd(&opt,"bgcol",'t',&bgtxt);


#ifdef _XLIB_ 
  OptionAdd(&opt,"display",'t',&display_name);
  OptionAdd(&opt,"xoff",'i',&xdoff);
  OptionAdd(&opt,"yoff",'i',&ydoff);
#endif

  arg=OptionProcess(1,argc,argv,&opt,NULL);   

  if (help==1) {
    OptionPrintInfo(stdout,hlpstr);
    exit(0);
  }

  if (option==1) {
    OptionDump(stdout,&opt);
    exit(0);
  }

 

  if (arg<argc) {
    fp=fopen(argv[arg],"r");
    if (fp==NULL) {
      fprintf(stderr,"Error opening file.\n");
      exit(-1);
    }
  } else fp=stdin;
 
  src=FrameBufferLoadPPMX(fp);

  if (src==NULL) {
    fprintf(stderr,"Error decoding image.\n");
    exit(-1);
  }
  if (arg<argc) fclose(fp);

  bgcolor=FrameBufferColor(0x00,0x00,0x00,0xff);

  if (bgtxt !=NULL) {
     sscanf(bgtxt,"%x",&bgcolor);
     bgcolor=bgcolor | 0xff000000;
  }
  
  
  if (scale<=0) scale=0.5;
  
  if (scale !=100) {
    wdt=src->wdt*scale/100.0;
    hgt=src->hgt*scale/100.0;
  } else {
    wdt=src->wdt;
    hgt=src->hgt;
  }

  if ((wdt==0) || (hgt==0)) {
    fprintf(stderr,"Invalid image size.\n");
    exit(-1);
  }

  dst=FrameBufferMake(NULL,wdt,hgt,24);
  FrameBufferClear(dst,bgcolor,0x0f);

  if (cflg !=0) { /* plot checker board */
    int x,y;
    int c=0,d=0;
    for (x=0;x<wdt;x+=8) {
      c=d;
      d=!d;
      for (y=0;y<hgt;y+=8) {
        c=!c;
        if (c==0) FrameBufferRectangle(dst,NULL,x,y,8,8,1,
                             0xffc0c0c0,0x0f,0,NULL,NULL);
        else FrameBufferRectangle(dst,NULL,x,y,8,8,1,
                             0xffffffff,0x0f,0,NULL,NULL);
     
      }
    }
  } 


  if (scale==100)
    FrameBufferImage(dst,NULL,src,0x0f,0,0,0,NULL);  
  else {
    m.a=scale/100.0;
    m.b=0;
    m.c=0;
    m.d=scale/100.0;
    FrameBufferImage(dst,&m,src,0x0f,0,0,sflg,NULL); 
  }  

#ifdef _XLIB_
  dp=XwinOpenDisplay(display_name,&xdf);
 
  if (dp==NULL) {
    fprintf(stderr,"Could not open display.\n");
    exit(-1);
  }

  if (xdoff==-1) xdoff=(dp->wdt-dst->wdt)/2;
  if (ydoff==-1) ydoff=(dp->hgt-dst->hgt)/2;

  win=XwinMakeWindow(xdoff,ydoff,dst->wdt,dst->hgt,0,
                       dp,name,
                       name,argv[0],name,argc,argv,&xdf);
  if (win==NULL) {
    fprintf(stderr,"Could not create window.\n");
    exit(-1);
  }

  XwinFrameBufferWindow(dst,win);

  XwinShowWindow(win);

  XwinDisplayEvent(dp,1,&win,1,NULL);

  XwinFreeWindow(win);
  XwinCloseDisplay(dp); 
#endif

  return 0;
}




