/* key.h
   =====
   Author: R.J.Barnes
*/



/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




struct key {
  int max;
  unsigned char *a;
  unsigned char *r;
  unsigned char *g;
  unsigned char *b;
};

int load_key(FILE *fp,struct key *key);
