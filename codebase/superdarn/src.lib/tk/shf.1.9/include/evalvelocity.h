/* evalvelocity.h
   ============== 
   Author R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef _EVALVELOCITY_H
#define _EVALVELOCITY_H


double *CnvMapEvalThetaCoef(int Lmax,double *coef,double *theta,int n,
		    double latmin);

double *CnvMapEvalPhiCoef(int Lmax,double *coef,double *theta,int n);

void CnvMapEvalComponent(int Lmax,double *ecoef,double *plm,
                      double *phi,int n,double *ecomp);


void CnvMapEvalVelocity(int Lmax,double *coef,double *plm,
		       struct CnvGrid *vptr,double latmin,
                       struct CnvMapData *ptr);

#endif
