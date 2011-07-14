/* rxml.h
   ===== 
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#ifndef _RXML_H
#define _RXML_H

struct XMLinterface {
 struct {
    int (*func)(char *,int,void *);
    void *data;
  } text;

  struct {
    int (*func)(char *,char,int,char **,char **,char *,int,void *);
    void *data;
  } start;


  struct {
    int (*func)(char *,char *,int,void *);
    void *data;
  } end;


  struct {
    int (*func)(char *,int,void *);
    void *data;
  } comment;

  struct {
    int (*func)(char *,int,void *);
    void *data;
  } process;
};

struct XMLdata {
  int sze;
  int max;
  int stp;
  char *buf;
  struct XMLinterface interface;
};


struct XMLdata *XMLMake();
 
void XMLFree(struct XMLdata *ptr);
 

int XMLSetText(struct XMLdata *ptr,
             int (*func)(char *,int,void *),void *data);
  

int XMLSetProcess(struct XMLdata *ptr,
		int (*func)(char *,int,void *),void *data);
  

int XMLSetComment(struct XMLdata *ptr,
		int (*func)(char *,int,void *),void *data);
  
int XMLSetStart(struct XMLdata *ptr,
		int (*func)(char *,char,int,char **,char **,
                         char *,int,void *),void *data);
int XMLSetEnd(struct XMLdata *ptr,
	    int (*func)(char *,char *,int,void *),void *data);

int XMLDecode(struct XMLdata *ptr,char *buf,int sze);
  
int XMLCallEnd(struct XMLdata *ptr,char *name,char *buf,int sze);

int XMLCallStart(struct XMLdata *ptr,
                 char *name,char end,int atnum,char **atname,char **atval,
                 char *buf,int sze);
#endif
