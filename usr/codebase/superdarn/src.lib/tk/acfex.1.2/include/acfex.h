/* acfex.h
   =======
   Author: R.J.Barnes
*/

/* 
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#ifndef _ACFEX_H
#define _ACFEX_H

int ACFexCalculate(struct TSGprm *prm,int16 *iqptr,int iqnum,
		 int nave,int nsample,int roffset,int ioffset,
                 int mplgs,int lagnum,int *lagtable[2],int *lagsum,
                 float *pwr0,float *acfbuf,float *noise);

#endif
