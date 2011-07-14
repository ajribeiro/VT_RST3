/* indexlegendre.c
   =============== 
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>




int CnvMapIndexLegendre(int L,int m) {
  if (L==0) return 0;
  if (m==0) return L*L;
  return (L*L)+(2*m)-1;
}

void CnvMapLegendreIndex(int k,int *L,int *m) {
 
  *L=sqrt(k);
  if (*L**L==k) *m = 0; 
  else *m = (k + 1 - *L**L)/2;
  if (CnvMapIndexLegendre(*L,*m) !=k) *m=-*m;
}
