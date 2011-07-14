/* make.c
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
#include "rps.h"



struct PostScript *PostScriptMake() {
  struct PostScript *ptr;
  ptr=malloc(sizeof(struct PostScript));
  ptr->text.func=NULL;
  ptr->text.data=NULL;
  return ptr;
}

void PostScriptFree(struct PostScript *ptr) {
  if (ptr==NULL) return;
  free(ptr);
};

int PostScriptSetText(struct PostScript *ptr,
                      int (*text)(char *,int,void *),void *data) {
  if (ptr==NULL) return -1;
  ptr->text.func=text;
  ptr->text.data=data;
  return 0;
}

