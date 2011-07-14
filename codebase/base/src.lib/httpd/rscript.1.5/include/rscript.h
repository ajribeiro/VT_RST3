/* rscript.h
   ========= 
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef _RSCRIPT_H
#define _RSCRIPT_H

struct ScriptData {
  int depth;
  int sze;
  int max;
  int stp;
  char *buf;

  struct {
    int (*func)(char *,int,void *);
    void *data;
  } text;
 
};

struct ScriptData *ScriptMake();
void ScriptFree(struct ScriptData *ptr);
 
int ScriptSetText(struct ScriptData *ptr,
	       int (*text)(char *,int,void *),void *data);

int ScriptDecode(struct ScriptData *ptr,char *buf,int sze);
  
#endif
