/* siteglobal.h
   ============ 
   Author: R.J.Barnes
*/
   

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#ifndef _SITEGLOBAL_H
#define _SITEGLOBAL_H

extern int sock;
extern char server[256];
extern int port;
extern int num_transmitters;
extern struct timeval tock;
extern struct ControlPRM rprm;
extern struct ControlData rdata;
extern struct BadTR badtrdat;
extern struct TXStatus txstatus;
extern struct SiteLibrary sitelib;
extern int *exit_flag;
extern int cancel_count;


#endif
