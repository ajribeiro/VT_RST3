/* errlog.h
   ========
   Author: R.J.Barnes
*/


/* 
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#ifndef _ERRLOG_H
#define _ERRLOG_H

#define ERROR_MSG 'M'
#define ERROR_OK 'O'
#define ERROR_FAIL 'F'

int ErrLog(int sock,char *name,char *buffer);

#endif
