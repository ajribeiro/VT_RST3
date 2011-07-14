/* shfconst.h
   ==========
   Author: R.J.Barnes
*/


/*
 (c) 2010 JHU/APL & Others - Please Consult LICENSE.superdarn-rst.3.2-beta-4-g32f7302.txt for more information.
 
 
 
*/



#ifndef _SHFCONST_H
#define _SHFCONST_H

/* radius of the earth (polar radius) */
#define Re (6357.0*1000.0)      

/* assummed altitude of scattering region */
#define Altitude (300.0*1000.0)

/* Magnetic field strength at N pole */
#define BNorth (-0.58e-4)

/* Magnetic field strength at S pole */
#define BSouth (-0.68e-4)
/* note: we use a negative value even for S pole, because the code for handling
   the S pole data does its own switching */

#define Radial_Dist (Re + Altitude)

#endif
