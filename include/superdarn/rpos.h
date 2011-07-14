/* rpos.h
   ======
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef _RPOS_H
#define _RPOS_H


struct RPos {
  double gdlat;
  double gdlon;
  double boresite;
  double bmwidth;
  double rxris;
};

void RPosGeo(int center,int bcrd,int rcrd,
                struct RadarSite *pos,
                int lagfr,int smsep,int rxrise,double height,
                double *rho,double *lat,double *lng);
void RPosMag(int center,int bcrd,int rcrd,
                struct RadarSite *pos,
                int lagfr,int smsep,int rxrise,double height,
                double *rho,double *lat,double *lng);

void RPosCubic(int center,int bcrd,int rcrd,
                struct RadarSite *pos,
                int lagfr,int smsep,int rxrise,double height,
                double *x,double *y,double *z);

void RPosGeoGS(int center,int bcrd,int rcrd,
                struct RadarSite *pos,
                int lagfr,int smsep,int rxrise,double height,
                double *rho,double *lat,double *lng);
void RPosMagGS(int center,int bcrd,int rcrd,
                struct RadarSite *pos,
                int lagfr,int smsep,int rxrise,double height,
                double *rho,double *lat,double *lng);

void RPosCubicGS(int center,int bcrd,int rcrd,
              struct RadarSite *pos,
              int lagfr,int smsep,int rxrise,double height,
              double *x,double *y,double *z);



#endif
