/* evallegendre.h
   ==============
   Author R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




#ifndef _EVALLEGENDRE_H
#define _EVALLEGENDRE_H



#define PLM(L,m,i) *(plm+(m)*n+(L)*(Lmax+1)*n+(i))
#define a(k) *(coef+4*(k)+2)


void CnvMapEvalLegendre(int Lmax,double *x,int n,double *plm);
int CnvMapIndexLegendre(int,int); 

#endif


