/* getstring.c
   =========== 
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rxml.h"
#include "rxmldb.h"



char *getDBstring(struct XMLDBbuffer *ptr) {
  int s=0;
  char *str=NULL;
  char zero[1];
  struct XMLDBbuffer *decode=NULL;  

  zero[0]=0;
  decode=XMLDBCopyBuffer(ptr);
  if (decode==NULL) return NULL;
  s=XMLDBAddBuffer(decode,zero,1);
  if (s !=0) {
    XMLDBFreeBuffer(decode);
    return NULL;
  }
  str=decode->buf;
  free(decode);
  return str;
}

