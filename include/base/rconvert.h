/* rconvert.h
   ==========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#ifndef _RCONVERT_H
#define _RCONVERT_H

int ConvertBitOrder();
void ConvertToLong(unsigned char *cnv,int64 *val);
void ConvertToInt(unsigned char *cnv,int32 *val);
void ConvertToShort(unsigned char *cnv,int16 *val);
void ConvertToDouble(unsigned char *cnv,double *val);
void ConvertToFloat(unsigned char *cnv,float *val);
void ConvertFromFloat(float val,unsigned char *cnv);
void ConvertFromDouble(double val,unsigned char *cnv);
void ConvertFromLong(int64 val,unsigned char *cnv);
void ConvertFromInt(int32 val,unsigned char *cnv);
void ConvertFromShort(int16 val,unsigned char *cnv);
void ConvertBlock(unsigned char *cnv,int *pattern);
int ConvertFreadLong(FILE *fp,int64 *val);
int ConvertFreadInt(FILE *fp,int32 *val);
int ConvertFreadShort(FILE *fp,int16 *val);
int ConvertFreadDouble(FILE *fp,double *val);
int ConvertFreadFloat(FILE *fp,float *val);
int ConvertFwriteFloat(FILE *fp,float val);
int ConvertFwriteDouble(FILE *fp,double val);
int ConvertFwriteLong(FILE *fp,int64 val);
int ConvertFwriteInt(FILE *fp,int32 val);
int ConvertFwriteShort(FILE *fp,int16 val);
int ConvertReadLong(int fp,int64 *val);
int ConvertReadInt(int fp,int32 *val);
int ConvertReadShort(int fp,int16 *val);
int ConvertReadDouble(int fp,double *val);
int ConvertReadFloat(int fp,float *val);
int ConvertWriteFloat(int fp,float val);
int ConvertWriteDouble(int fp,double val);
int ConvertWriteLong(int fp,int32 val);
int ConvertWriteInt(int fp,int32 val);
int ConvertWriteShort(int fp,int16 val);

int ConvertReadLongZ(gzFile file,int64 *val);
int ConvertReadIntZ(gzFile file,int32 *val);
int ConvertReadShortZ(gzFile file,int16 *val);
int ConvertReadDoubleZ(gzFile file,double *val);
int ConvertReadFloatZ(gzFile file,float *val);
int ConvertWriteFloatZ(gzFile file,float val);
int ConvertWriteDoubleZ(gzFile file,double val);
int ConvertWriteLongZ(gzFile file,int64 val);
int ConvertWriteIntZ(gzFile file,int32 val);
int ConvertWriteShortZ(gzFile file,int16 val);





#endif



