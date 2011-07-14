/* shmem.h
   =======
   Author R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#ifndef _SHMEM_H
#define _SHMEM_H

unsigned char *ShMemAlloc(char *memname,int size,int flags,int unlink,
			  int *fdptr);
int ShMemFree(unsigned char *p,char *memname,int size,int unlink,int fd);

#endif
