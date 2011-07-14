/* raw_read.h
   ==========
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



struct rawfp {
  int rawfp;
  int inxfp;
  struct stat rstat;
  struct stat istat;
  double ctime;
  double stime;
  int frec;
  int rlen;
  int ptr;
  int (*rawread)(struct rawfp *ptr,struct rawdata *raw_data);

};

int raw_read(struct rawfp *fp,struct rawdata *);
int raw_read_data(struct rawfp *fp,struct rawdata *);
int raw_seek(struct rawfp *ptr,int yr,int mo,int dy,int hr,int mt,int sc,
	     double *atme);
void raw_close(struct rawfp *ptr);
struct rawfp *raw_open(char *rawfile,char *inxfile);



