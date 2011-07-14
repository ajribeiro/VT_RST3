/* lmfit.h
   ==========
*/

#ifndef _lmfit_test_H
#define _lmfit_test_H

#ifndef PULSE_SIZE
#define PULSE_SIZE 256
#endif

void lmfit_test(struct RadarParm *prm,struct RawData *ptr,
                struct FitData *fit,struct FitBlock *fblk);

#endif
