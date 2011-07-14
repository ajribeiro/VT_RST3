/* pipe.h
   ======
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/




int pipewrite(int fildes,char st,
	      unsigned char *buffer,unsigned int size);

int piperead(int fildes,unsigned char **buffer,unsigned char *st);
