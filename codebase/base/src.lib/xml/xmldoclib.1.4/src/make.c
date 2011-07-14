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
#include "rxml.h"
#include "rxmldb.h"
#include "entity.h"
#include "tagdb.h"
#include "rxmldoc.h"



struct XMLdocdata *XMLdocMake() {
  struct XMLdocdata *ptr=NULL;

  ptr=malloc(sizeof(struct XMLdocdata));
  memset(ptr,0,sizeof(struct XMLdocdata));

  /* set up root element handler */

  ptr->ent=EntityMake();
  ptr->tag=TagDBMake(NULL);
  TagDBSetText(ptr->tag,EntityDecode,ptr->ent);
  return ptr;

}

void XMLdocFreeMod(struct XMLdocmod *ptr) {
  if (ptr==NULL) return;
  if (ptr->name !=NULL) free(ptr->name);
  if (ptr->path !=NULL) free(ptr->path);
  if (ptr->tagdb !=NULL) TagDBFreeTable(ptr->tagdb);
  if (ptr->action !=NULL) XMLDBFreeBuffer(ptr->action);
  free(ptr);
}

void XMLdocFreeElement(struct XMLdocelement *ptr) {
  int i;
  if (ptr==NULL) return;
  if (ptr->name !=NULL) free(ptr->name);
  if (ptr->path !=NULL) free(ptr->path);
  if (ptr->tagdb !=NULL) TagDBFreeTable(ptr->tagdb);
  if (ptr->action !=NULL) XMLDBFreeBuffer(ptr->action);
  if (ptr->defval !=NULL) XMLDBFreeBuffer(ptr->defval);
  if (ptr->mod.ptr !=NULL) {
    for (i=0;i<ptr->mod.num;i++) {
      XMLdocFreeMod(ptr->mod.ptr[i]);
    }
    free(ptr->mod.ptr);
  }
  free(ptr);
}





void XMLdocFree(struct XMLdocdata *ptr) {
  int i;
  if (ptr==NULL) return;
  if (ptr->ent !=NULL) EntityFree(ptr->ent);
  if (ptr->tag !=NULL) TagDBFree(ptr->tag);
  if (ptr->tagdb !=NULL) TagDBFreeTable(ptr->tagdb);
  

  /* free up the rest of this stuff */
  if (ptr->root !=NULL) XMLDBFreeBuffer(ptr->root);
  if (ptr->xml.ptr !=NULL) {
    for (i=0;i<ptr->xml.num;i++) {
      XMLdocFreeElement(ptr->xml.ptr[i]);
    }
    free(ptr->xml.ptr);
  }
  free(ptr);
  return;
}








