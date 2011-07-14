/* geotail.h
   =========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




int geolep_pos(CDFid id,struct posdata *ptr,double stime,double etime);
int geolep_plasma(CDFid id,struct plasmadata *ptr,double stime,double etime);
int geomgf_pos(CDFid id,struct posdata *ptr,double stime,double etime);
int geomgf_imf(CDFid id,struct imfdata *ptr,double stime,double etime);
  
int geocpi_plasma(CDFid id,struct plasmadata *ptr,double stime,double etime);
