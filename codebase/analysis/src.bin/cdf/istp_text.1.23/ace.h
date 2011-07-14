/* ace.h
   =====
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




int aceswe_pos(CDFid id,struct posdata *ptr,double stime,double etime);  
int aceswe_plasma(CDFid id,struct plasmadata *ptr,double stime,double etime);
int acemfi_imf(CDFid id,struct imfdata *ptr,double stime,double etime,int cnv);
 
