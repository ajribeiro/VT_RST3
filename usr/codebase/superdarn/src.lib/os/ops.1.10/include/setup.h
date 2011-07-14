/* setup.h
   ======= 
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

#ifndef _SETUP_H
#define _SETUP_H

#define START_STRING "PROGRAM START->"

int OpsSetupCommand(int argc,char *argv[]);
int OpsStart(char *ststr);
int OpsFitACFStart();
void OpsLogStart(int sock,char *name,int argc,char *argv[]);
void OpsSetupTask(int tnum,struct TCPIPMsgHost *task,int sock,char *name);
void OpsSetupShell();
  
#endif
