/* rmsg.h
   =====
   Author: R.J.Barnes
*/

/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/

/*
 $Log: rmsg.h,v $
 Revision 1.4  2008/03/15 15:39:46  code
 Added offset into the samples for IQ data to handle stereo.

 Revision 1.3  2008/03/14 21:56:40  code
 Added IQS_TYPE.

 Revision 1.2  2008/03/14 20:26:50  code
 Added the raw I&Q data type.

 Revision 1.1  2004/07/12 22:36:36  barnes
 Initial revision

*/

#ifndef _RMSG_H
#define _RMSG_H

#define PRM_TYPE 0
#define FIT_TYPE 1
#define RAW_TYPE 2
#define NME_TYPE 3

/*  type for the IQ data 
 *
 *  IQ_TYPE = IQ data block 
 *  IQS_TYPE = name of the shared memory object containing the samples.
 *  IQO_TYPE = offset into the shared memory to take samples.
 */

#define BADTR_TYPE 254

#define IQ_TYPE 255
#define IQS_TYPE 256
#define IQO_TYPE 257



#define MAX_BUF 32

#define TASK_OPEN	'O'
#define TASK_CLOSE	'C'	
#define TASK_QUIT	'Q'		
#define TASK_DATA   'd'
#define TASK_RESET  'r'

#define TASK_OK	 0	
#define TASK_ERR	'R'	
#define UNKNOWN_TYPE	0x7f

struct RMsgData {
  int type;
  int tag;
  size_t size;
  int index;
};
   
struct RMsgBlock {
  int num;
  size_t tsize;
  struct RMsgData data[MAX_BUF];
  unsigned char *ptr[MAX_BUF];
};

#endif
