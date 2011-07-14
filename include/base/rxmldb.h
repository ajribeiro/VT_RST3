/* rxmldb.h
   ======== 
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#ifndef _RXMLDB_H
#define _RXMLDB_H

struct XMLDBbuffer {
  int sze; 
  int max;
  int stp; 
 char *buf;
};

struct XMLDBtree {
  int depth;
  char **name;
};

struct XMLDBelement {
  char *name;
  char end;
  int atnum;
  char **atname; 
  char **atval;
  struct XMLDBbuffer *data;
}; 

struct XMLDBtable {
  int num;
  struct XMLDBelement **element;
};

struct XMLDBdata {
  struct XMLdata *ptr;
  struct XMLDBtree *tree;
  struct XMLDBtable *doc;
  struct XMLDBbuffer *buf;
  struct XMLDBtable *table;

  struct {
    int (*func)(struct XMLDBtable *,struct XMLDBtable *,void *);
    void *data;
  } text;
 
  int depth;
};

struct XMLDBbuffer *XMLDBCopyBuffer(struct XMLDBbuffer *);

struct XMLDBbuffer *XMLDBMakeBuffer(int stp);
void XMLDBFreeBuffer(struct XMLDBbuffer *ptr);
int XMLDBAddBuffer(struct XMLDBbuffer *ptr,char *str,int sze);

struct XMLDBelement *XMLDBMakeElement(char *name,char end,int atnum,
				      char **atname,char **atval,int stp);
void XMLDBFreeElement(struct XMLDBelement *ptr);


struct XMLDBtable *XMLDBMakeTable();
void XMLDBFreeTable(struct XMLDBtable *ptr);
int XMLDBRemoveTable(struct XMLDBtable *ptr);
int XMLDBAddTable(struct XMLDBtable *ptr,struct XMLDBelement *element);


struct XMLDBdata *XMLDBMake(struct XMLdata *xml);
void XMLDBFree(struct XMLDBdata *ptr);  

int XMLDBSetTree(struct XMLDBdata *ptr,struct XMLDBtree *tree);

int XMLDBSetText(struct XMLDBdata *ptr,
	      int (*text)(struct XMLDBtable *,struct XMLDBtable *,void *),
              void *data);

int XMLDBElementStart(char *name,char end,int atnum,char **atname,char **atval,
		      char *buf,int sze,void *data);

int XMLDBElementEnd(char *name,char *buf,int sze,void *data);

int XMLDBElementText(char *buf,int sze,void *data);


int XMLDBPeerStart(char *name,char end,int atnum,char **atname,char **atval,
		   char *buf,int sze,void *data);

int XMLDBPeerEnd(char *name,char *buf,int sze,void *data);

int XMLDBStart(char *name,char end,int atnum,char **atname,char **atval,
	       char *buf,int sze,void *data);

int XMLDBEnd(char *name,char *buf,int sze,void *data);

struct XMLDBtree *XMLDBMakeTree();
void XMLDBFreeTree(struct XMLDBtree *ptr);
int XMLDBBuildTree(char *path,char delim,struct XMLDBtree *ptr);

#endif

  





  
