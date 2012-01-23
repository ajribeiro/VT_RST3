/* lmfit2.h
   ==========
*/

#ifndef _lmfit2_H
#define _lmfit2_H

#ifndef PULSE_SIZE
#define PULSE_SIZE 256
#endif


void lmfit2(struct RadarParm *prm,struct RawData *ptr,
                struct FitData *fit,struct FitBlock *fblk, int print);
int singlefit2(int m, int n, double *p, double *deviates,
                        double **derivs, void *private);

#endif
