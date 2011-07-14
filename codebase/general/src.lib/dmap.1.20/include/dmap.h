/* dmap.h
   ====== 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef _DMAP_H
#define _DMAP_H


#define DATACHAR 1
#define DATASHORT 2
#define DATAINT 3
#define DATAFLOAT 4
#define DATADOUBLE 8
#define DATASTRING 9


/* Define an unique code value for this version of the library. */

#define DATACODE  0x00010001


union DataMapPointer {
  char *cptr;
  int16 *sptr;
  int32 *iptr;
  float *fptr;
  double *dptr;
  void *vptr;
  unsigned int *optr;
};

struct DataMapScalar {
  char *name;
  unsigned char type;
  unsigned char mode;
  union DataMapPointer data;
};

struct DataMapArray {
    char *name;
    unsigned char type;
    unsigned char mode;
    int32 dim;
    int32 *rng;
    union DataMapPointer data;
};

struct DataMap {
  int sze;
  unsigned char *buf;
  int snum;
  int anum;
  struct DataMapScalar **scl;
  struct DataMapArray **arr;
}; 

struct DataMap *DataMapMake();

struct DataMapScalar* DataMapMakeScalar(char *name,int mode,int type,
                                                void *data);
 
void DataMapFreeScalar(struct DataMapScalar *ptr);

int DataMapAddScalar(struct DataMap *ptr,
                         char *name,int type,void *data);


void *DataMapStoreScalar(struct DataMap *ptr,
		       char *name,int type,void *data);


struct DataMapArray* DataMapMakeArray(char *name,int mode,int type,int dim,
                                      int32 *rng,void *data);

void DataMapFreeArray(struct DataMapArray *ptr);
 
int DataMapAddArray(struct DataMap *ptr,
                    char *name,int type,int dim,
                    int32 *rng,void *data);
 
void *DataMapStoreArray(struct DataMap *ptr,
			char *name,int type,int dim,int32 *rng,void *data);

int DataMapSize(struct DataMap *write);

unsigned char *DataMapEncodeBuffer(struct DataMap *ptr,int *size);

int DataMapWrite(int fid,struct DataMap *ptr);
 
void DataMapFree(struct DataMap *ptr);
struct DataMap *DataMapRead(int fid);

int DataMapFwrite(FILE *fp,struct DataMap *ptr);


struct DataMap *DataMapFread(FILE *fp);

struct DataMap *DataMapDecodeBuffer(unsigned char *buf,int size);

struct DataMap *DataMapReadBlock(int fid,int *s);
struct DataMap *DataMapFreadBlock(FILE *fp,int *s);


struct DataMap *DataMapReadBlockZ(gzFile file,int *s);
struct DataMap *DataMapReadZ(gzFile file);
int DataMapWriteZ(gzFile file,struct DataMap *ptr);




#endif
