/* radarshell.h
   ============
   Author: R.J.Barnes
*/


/* 
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#ifndef _RADARSHELL_H
#define _RADARSHELL_H

#define STR_MAX 128 

enum {  /* variable types */
  var_SHORT,
  var_INT,
  var_LONG,
  var_FLOAT,
  var_DOUBLE,
  var_STRING
};

struct RShellEntry {
  char *name; 
  int type;
  void *data;
};

struct RShellTable {
  int num;
  struct RShellEntry *ptr;
};

struct RShellBuffer {
  int num;
  size_t len;
  size_t *off;
  char *buf;
};

struct RShellBuffer *RShellBufferMake();
int RShellBufferAlloc(struct RShellBuffer *ptr,void *buf,int sze);
void *RShellBufferRead(struct RShellBuffer *ptr,int num);
void RShellBufferFree(struct RShellBuffer *ptr);



int RadarShell(int sock,struct RShellTable *rptr);
int RadarShellAdd(struct RShellTable *rptr,
		  char *name,int type,void *data);
void RadarShellFree(struct RShellTable *rptr);
struct RShellEntry *RadarShellRead(struct RShellTable *rptr,int num);
struct RShellEntry *RadarShellFind(struct RShellTable *rptr,char *name);

int RadarShellParse(struct RShellTable *rptr,char *name,...);






#endif
