/* msgmem.h
   ========
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



int write_raw(char *buf,int sze); 
void read_sock(fd_set *fdset,char *tmp_buf,int tmp_sze);
int write_sock();



