/* evalpotential.c
   ===============
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "evallegendre.h"




void CnvMapEvalPotential(int Lmax,int n,double *coef,double *plm,
		    double *phi,double *v) {

  int i,m,k,L;

  for (i=0;i<n;i++) v[i]=0.0;
  for (m=0;m<=Lmax;m++) {
    for (L=m;L<=Lmax;L++) {
      k=CnvMapIndexLegendre(L,m);
      for (i=0;i<n;i++) {
        if (m==0) v[i]=v[i]+a(k)*PLM(L,0,i);
        else v[i]=v[i]+a(k)*cos(m*phi[i])*PLM(L,m,i)+
                  a(k+1)*sin(m*phi[i])*PLM(L,m,i);
      }
    }
  }
}












