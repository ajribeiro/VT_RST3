
/* lmfit.c
   ==========
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <zlib.h>
#include "rtypes.h"
#include "rmath.h" 
#include "nrfit.h" 
#include "rprm.h"
#include "rawdata.h" 
#include "fitdata.h"
#include "fitblk.h"
#include "lmfit.h"
#include "badsmp.h"
#include "badlags.h"
#include "mpfit.h"


/* dbl_cmp
   =========
   Author: R.J.Barnes & K. Baker
*/
int lm_dbl_cmp(const void *x,const void *y) 
{
  double *a,*b;
  a=(double *) x;
  b=(double *) y;
  if (*a > *b) return 1;
  else if (*a == *b) return 0;
  else return -1;
}


void setup_fblk(struct RadarParm *prm, struct RawData *raw,struct FitBlock *input)
{
  int i,j,n;
  void *tmp=NULL;

  if (prm->time.yr < 1993) input->prm.old=1;

  input->prm.xcf=prm->xcf;
  input->prm.tfreq=prm->tfreq;
  input->prm.noise=prm->noise.search;
  input->prm.nrang=prm->nrang;
  input->prm.smsep=prm->smsep;
  input->prm.nave=prm->nave;
  input->prm.mplgs=prm->mplgs;
  input->prm.mpinc=prm->mpinc;
  input->prm.txpl=prm->txpl;
  input->prm.lagfr=prm->lagfr;
  input->prm.mppul=prm->mppul;
  input->prm.bmnum=prm->bmnum;
  input->prm.cp=prm->cp;
  input->prm.channel=prm->channel;
  input->prm.offset=prm->offset; /* stereo offset */


  /* need to incorporate Sessai's code for setting the offset
     for legacy data here.
  */


  if (input->prm.pulse==NULL) tmp=malloc(sizeof(int)*input->prm.mppul);
  else tmp=realloc(input->prm.pulse,sizeof(int)*input->prm.mppul);
  if (tmp==NULL) return;
  input->prm.pulse=tmp;
  for (i=0;i<input->prm.mppul;i++) input->prm.pulse[i]=prm->pulse[i];

  for (n=0;n<2;n++) {
    if (input->prm.lag[n]==NULL) tmp=malloc(sizeof(int)*(input->prm.mplgs+1));
    else tmp=realloc(input->prm.lag[n],sizeof(int)*(input->prm.mplgs+1));
    if (tmp==NULL) return;
    input->prm.lag[n]=tmp;
    for (i=0;i<=input->prm.mplgs;i++) input->prm.lag[n][i]=prm->lag[n][i];
  }



  if (input->prm.pwr0==NULL) tmp=malloc(sizeof(int)*input->prm.nrang);
  else tmp=realloc(input->prm.pwr0,sizeof(int)*input->prm.nrang);
  if (tmp==NULL) return;
  input->prm.pwr0=tmp;

  if (input->acfd==NULL) tmp=malloc(sizeof(struct complex)*input->prm.nrang*
                                    input->prm.mplgs);
  else tmp=realloc(input->acfd,sizeof(struct complex)*input->prm.nrang*
                                   input->prm.mplgs);
  if (tmp==NULL) return;
  input->acfd=tmp;

  if (input->xcfd==NULL) tmp=malloc(sizeof(struct complex)*input->prm.nrang*
                                    input->prm.mplgs);
  else tmp=realloc(input->xcfd,sizeof(struct complex)*input->prm.nrang*
                                   input->prm.mplgs);
  if (tmp==NULL) return;
  input->xcfd=tmp;

  memset(input->acfd,0,sizeof(struct complex)*input->prm.nrang*
                                   input->prm.mplgs);
  memset(input->xcfd,0,sizeof(struct complex)*input->prm.nrang*
                                   input->prm.mplgs);



  for (i=0;i<input->prm.nrang;i++) {
    input->prm.pwr0[i]=raw->pwr0[i];

    if (raw->acfd[0] !=NULL) {
      for (j=0;j<input->prm.mplgs;j++) {
        input->acfd[i*input->prm.mplgs+j].x=raw->acfd[0][i*input->prm.mplgs+j];
        input->acfd[i*input->prm.mplgs+j].y=raw->acfd[1][i*input->prm.mplgs+j];
      }
    }
    if (raw->xcfd[0] !=NULL) {
      for (j=0;j<input->prm.mplgs;j++) {
        input->xcfd[i*input->prm.mplgs+j].x=raw->xcfd[0][i*input->prm.mplgs+j];
        input->xcfd[i*input->prm.mplgs+j].y=raw->xcfd[1][i*input->prm.mplgs+j];
      }
    }
  }

  return;
}

double calc_err(double w_guess, struct RawData *raw, float *good_lags, int goodcnt,
              int R, float *lagpwr,double pwr, struct RadarParm *prm)
{

  int j, i, L=-1, p, lag;
  double error_guess = 0, phi, data_phi, model_phi, delta_guess=0;

  for (j=0;j<goodcnt;j++)
  {
      lag = good_lags[j];
      if((prm->cp == 3310 || prm->cp == 503 || prm->cp == -503) && prm->mplgs == 18)
        L = lag;
      else 
        for(i=0;i<prm->mplgs;i++)
          if(abs(prm->lag[0][i]-prm->lag[1][i]) == lag)
          {
            L = i;
            break;
          }

      phi = lag*w_guess;
      p = phi/360;
      model_phi = phi - p*360;

      data_phi = atan2(raw->acfd[1][R*prm->mplgs+L],raw->acfd[0][R*prm->mplgs+L])*180.0/PI;


      delta_guess = fabs(data_phi - model_phi);

      if(delta_guess>180.0) delta_guess = 360 - delta_guess;
 
      error_guess += delta_guess*delta_guess*lagpwr[lag]/pwr;
  }

  return sqrt(error_guess);
}

void ls_fit(float *x,float *y, int n, float *a, float *b)
{
  double sum_x = 0, sum_y = 0, sum_x2 = 0, sum_xy = 0;
  int i;

  for(i=0;i<n;i++)
  {
    sum_x += x[i];
    sum_y += y[i];
    sum_x2 += pow(x[i],2);
    sum_xy += x[i]*y[i];
  }

  *b = (n*sum_xy-sum_y*sum_x)/(n*sum_x2 - sum_x*sum_x);
  *a = sum_y/((float)n) - *b*(sum_x/((float)n));

  return;
}

double calc_phi0(float *x,float *y, float m, int n)
{
  double sum_x = 0, sum_y = 0, b;
  int i;

  for(i=0;i<n;i++)
  {
    sum_x += x[i];
    sum_y += y[i];
  }

  b = (sum_y/((float)n))-((m*sum_x)/((float)n));

  return b;
}

int singlefit(int m, int n, double *p, double *deviates,
                        double **derivs, void *private)
{

  int i;
  double tau,re,im,sig,wi,ti;

  struct datapoints *v = (struct datapoints *) private;
  double lag0mag = v->mag;
  double *x, *y, *ey;
  x = v->x;
  y = v->y;
  ey = v->ey;
  for (i=0; i<m; i++)
  {
    tau=x[i];
    re=y[i*2]; 
    im=y[i*2+1];
    sig=ey[i];
    ti=p[0];
    wi=p[1];
    lag0mag = p[2];
    /*fprintf(stderr,"%lf  %lf  %lf  %lf  %lf  %lf  %lf\n",tau,re,im,sig,ti,wi,lag0mag);*/
    deviates[i] = sqrt((pow(re-lag0mag*exp(-1.*tau/ti)*cos(wi*tau),2) +
                       pow(im-lag0mag*exp(-1.*tau/ti)*sin(wi*tau),2))/**sig*/);
  }

  return 0;
}

void lm_noise_stat(struct RadarParm *prm, struct RawData * raw,
                double * skynoise)
{
  int j=0, R, i=0;
  double * pwrd = malloc(prm->nrang*sizeof(double));
  if(prm->cp != 3310 && prm->cp != 503 && prm->cp != -503)
  {
    j=0;
    for(R=0;R<prm->nrang;R++)
    {
      pwrd[j] = sqrt(raw->acfd[0][R*prm->mplgs]*raw->acfd[0][R*prm->mplgs]);
      if(pwrd[j] > 0.)
        j++;
    }
    qsort(pwrd, j, sizeof(double), lm_dbl_cmp);
    if(j >= 10)
    {
      for(i=0;i<10;i++)
        *skynoise += pwrd[i];
      *skynoise /= 10.;
    }
    else
    {
      for(i=0;i<j;i++)
        *skynoise += pwrd[i];
      *skynoise /= (double)j;
    }
    if(*skynoise <= 1.) *skynoise = prm->noise.search;
  }
  else
    *skynoise = prm->noise.search;

  return;
}

double getguessex(int goodcnt, int nlags, int nslopes, struct exdatapoints * exdata,
                  int tfreq, int mpinc)
{

  double error_neg, error_pos, model_sd, model_min, model_mean,
          model_slope, diff=180./nslopes, w_guess,
          phi, model_vel_pos, data_phi, pwr=0, delta_pos, delta_neg;

  int i, j, lastlag=nlags-1, p, mininx, sct_flg, sderr=3, lag;


  double * model_phi    = malloc(sizeof(double)*(nslopes+1)*(lastlag+1));
  double * model_vels   = malloc(sizeof(double)*(2*nslopes+1));
  double * model_errors = malloc(sizeof(double)*(2*nslopes+1));
  double * data_phi_pos = malloc(sizeof(double)*(lastlag+1));
  double * data_phi_neg = malloc(sizeof(double)*(lastlag+1));

  /* Generate models that will be used in the velocity determination */
  for(i=0;i<=nslopes;i++)
  {
    model_slope = 180.0*i/nslopes;
    for(j=0;j<=lastlag;j++)
    {
      phi = j*model_slope;
      p = phi/360;
      model_phi[i*(lastlag+1)+j] = phi - p*360;
    }
    model_vel_pos = 2.9979E8/2.0*(1-1000.0*tfreq/
        (1000.0*tfreq+model_slope/360.0/(mpinc*1.0e-6)));
    model_vels[nslopes-i] = -model_vel_pos;
    model_vels[nslopes+i] =  model_vel_pos;
  }

  /* Determine Doppler velocity by comparing the phase with models */
  pwr = 0.0;
  for(i=0;i<goodcnt;i++)
  {
    data_phi=exdata[i].phase;
    data_phi_pos[i] = data_phi;
    data_phi_neg[i] = 360. - data_phi;
    if(data_phi<0)
    {
      data_phi_pos[i] += 360.;
      data_phi_neg[i]  = -data_phi;
    }
    pwr += exdata[i].lagpwr;
  }
  for(i=0;i<=nslopes;i++)
  {
    error_neg = 0;
    error_pos = 0;
    for(j=0;j<goodcnt;j++)
    {
      lag = exdata[j].lagnum;
      delta_pos = fabs(data_phi_pos[j] - model_phi[i*(lastlag+1)+lag]);
      delta_neg = fabs(data_phi_neg[j] - model_phi[i*(lastlag+1)+lag]);
      if (delta_pos>180.0) delta_pos = 360 - delta_pos;
      if (delta_neg>180.0) delta_neg = 360 - delta_neg;
      error_neg += delta_neg*delta_neg*exdata[j].lagpwr/pwr;
      error_pos += delta_pos*delta_pos*exdata[j].lagpwr/pwr;
    }
    error_neg = sqrt(error_neg);
    error_pos = sqrt(error_pos);
    model_errors[nslopes-i] = error_neg;
    model_errors[nslopes+i] = error_pos;
  }

  /*check for aliasing limit*/
  int concnt = 0;
  int cons = 1;
  int maxcons = 1;
  for(j=1;j<goodcnt;j++)
  {
    if(exdata[j].lagnum - exdata[j-1].lagnum == 1)
    {
      concnt++;
      cons++;
    }
    else
    {
      if(cons > maxcons)
        maxcons = cons;
      cons = 1;
    }
  }
  int alias = 1;
  /*if we don't have consecutive lags at least twice,
    or at least 3 consecutive lags once, then cut model range in half*/
  if(concnt >= 2 || maxcons >= 3)
    alias = 0;

  model_mean = 0.0;
  model_sd   = 0.0;
  model_min  = 1.0e30;
  mininx     = 0;
  for(i=0;i<=nslopes*2;i++)
  {
    model_mean += model_errors[i];
    if((model_errors[i]<model_min && !alias) ||
        (model_errors[i]<model_min && i > nslopes/2. && i < nslopes*1.5))
    {
      model_min = model_errors[i];
      mininx = i;
    }
  }
  model_mean = model_mean/(nslopes*2+1);

  for(i=0;i<=nslopes*2;i++)
    model_sd += (model_errors[i] - model_mean)*(model_errors[i] - model_mean);

  model_sd = sqrt(model_sd/(nslopes*2));
  sct_flg = (model_min < (model_mean - sderr*model_sd));
  w_guess = (mininx-nslopes)*diff;

	free(model_phi);
  free(model_vels);
  free(model_errors);
  free(data_phi_pos);
  free(data_phi_neg);


  return 2.9979E8/2.0*(1-1000.0*tfreq/(1000.0*tfreq+w_guess/360.0/(mpinc*1.0e-6)));



}

void lmfit(struct RadarParm *prm,struct RawData *raw,
              struct FitData *fit, struct FitBlock *fblk, int print)
{
  float minpwr  = 3.0;
  double skynoise = 0.;
  int   minlag  = 6;
  int availflg = 0;
  int pwr_flg,sct_flg;
  float a,b,siga,sigb,chi2,q;
  float *lagpwr=NULL,*logpwr=NULL,*good_lags=NULL;
  float lag0pwr,re,im,pwr;
  float fitted_width=0.0,fitted_power=0.0;
  int   *lag_avail=NULL,availcnt=0,goodcnt=0;
  int   lastlag,lag,i,j,R,L,mplgs,tauflg = 0;
  double acferr;

  /*variable needed for mpfit call*/
  mp_par    parssingle[3];
  mp_result result;
  mp_config config;
  double pdouble[6];
  double psingle[3];
  double w_limit,t_limit,t_if,w_if,lag0pwrf,v_if,f_if,lambda,tau,ref,imf;
  int status;
  double perrorsingle[3];
  float *sigma = malloc(prm->mplgs*sizeof(double));
  struct exdatapoints * exdata = malloc(prm->mplgs*sizeof(struct exdatapoints));

  int *badlag = malloc(prm->mplgs * sizeof(int));
  struct FitACFBadSample badsmp;


	/*check for tauscan*/
	if(prm->cp == 3310 || prm->cp == 503 || prm->cp == -503)
		tauflg = 1;

  /* Find the highest lag, and allocate memory */
  if(!((tauflg) && prm->mplgs == 18))
  {
    lastlag = 0;
    for (j=0;j<prm->mplgs;j++)
    {
      if (abs(prm->lag[0][j]-prm->lag[1][j])>lastlag)
        lastlag = abs(prm->lag[0][j]-prm->lag[1][j]);
    }
  }
  else
    lastlag=prm->mplgs-1;

  /*define some stuctures using # of lags*/
  lagpwr       = malloc(sizeof(float)*(lastlag+1));
  logpwr       = malloc(sizeof(float)*(lastlag+1));
  lag_avail    = malloc(sizeof(int)*(lastlag+1));
  good_lags    = malloc(sizeof(float)*(lastlag+1));


  /*setup fitblock parameter*/
  setup_fblk(prm, raw, fblk);

  FitSetRng(fit,fblk->prm.nrang);
  if(fblk->prm.xcf)
  {
   FitSetXrng(fit,fblk->prm.nrang);
   FitSetElv(fit,fblk->prm.nrang);
  }

  /*calculate noise levels*/
  lm_noise_stat(prm,raw,&skynoise);
  if(!tauflg)
  {
		/*check for stereo operation*/
    if(fblk->prm.channel==0) FitACFBadlags(&fblk->prm,&badsmp);
    else FitACFBadlagsStereo(&fblk->prm,&badsmp);
  }

  if(prm->cp == 153) mplgs = prm->mplgs - 1;
  else mplgs = prm->mplgs;


	if(print)
	{
		fprintf(stdout,"%d  %d  %lf  %d  %lf\n",prm->nrang,mplgs,skynoise,prm->tfreq,prm->mpinc*1.e-6);
		fprintf(stdout,"%d  %d  %d  %d  %d  %d  %d  %d\n",prm->stid,prm->time.yr,prm->time.mo,
									prm->time.dy,prm->time.hr,prm->time.mt,(int)prm->time.sc,prm->bmnum);
	}
  /* Loop every range gate and calculate parameters */
  for (R=0;R<prm->nrang;R++)
  {

    /*subtract noise level from lag 0*/
    raw->acfd[0][R*prm->mplgs] -= skynoise;

    /*initialize parameters*/
    fit->rng[R].v        = 0.;
    fit->rng[R].v_err    = HUGE_VAL;
    fit->rng[R].p_0      = 0.0;
    fit->rng[R].w_l      = 0.0;
    fit->rng[R].w_l_err  = 0.0;
    fit->rng[R].p_l      = 0.0;
    fit->rng[R].p_l_err  = 0.0;
    fit->rng[R].w_s      = 0.0;
    fit->rng[R].w_s_err  = 0.0;
    fit->rng[R].p_s      = 0.0;
    fit->rng[R].p_s_err  = 0.0;
    fit->rng[R].sdev_l   = 0.0;
    fit->rng[R].sdev_s   = 0.0;
    fit->rng[R].sdev_phi = 0.0;
    fit->rng[R].qflg     = 0;
		fit->rng[R].nump     = 0;
    fit->rng[R].gsct     = 0;
    availcnt = 0;

    /*calculate SNR of lag0power*/
    lag0pwr  = 10.0*log10((raw->acfd[0][R*prm->mplgs]+skynoise)/skynoise);

		/*output range gate and statistical fluctuation level*/
    if(print)
      fprintf(stdout,"%d  %lf\n",R,raw->acfd[0][R*prm->mplgs]/sqrt(1.0*prm->nave));

		/*Preliminaries, badlag checking, power level checking*/
		for(L=0;L<mplgs;L++)
		{
			/*not tauscan, check for badlags*/
			if(!tauflg) FitACFCkRng(R+1,badlag,&badsmp,&fblk->prm);
			/*tauscan, new ROS*/
			if(tauflg && prm->mplgs == 18) lag = L;
			/*old ROS*/
			else lag = abs(prm->lag[0][L] - prm->lag[1][L]);

			re  = raw->acfd[0][R*prm->mplgs+L];
      im  = raw->acfd[1][R*prm->mplgs+L];
			lagpwr[lag] = sqrt(re*re + im*im);

			if(tauflg)
				availflg = 1;
			else
			{
				if(badlag[L])
          availflg = 0;
        else
          availflg = 1;
			}

			if(availflg && lagpwr[lag]>raw->acfd[0][R*prm->mplgs]/sqrt(1.0*prm->nave))
      {
        lag_avail[availcnt] = lag;
        availcnt++;
      }
      else lagpwr[lag] = 0.0;
      if(print)
          fprintf(stdout,"%d  %lf  %lf  %d\n",lag,raw->acfd[0][R*prm->mplgs+L],raw->acfd[1][R*prm->mplgs+L],
																						(availflg && sqrt(re*re + im*im)>raw->acfd[0][R*prm->mplgs]/sqrt(1.0*prm->nave)));
		}
		if(tauflg)
			pwr_flg = (lag0pwr>=minpwr);
		else
		{
			pwr_flg = raw->acfd[0][R*prm->mplgs]>=skynoise;
			minlag = 4;
		}

    if(print)
      fprintf(stdout,"%d  %d\n",(pwr_flg),(availcnt>=minlag));

    /*if SNR is high enough and we have ge 6 good lags*/
    if((pwr_flg) && (availcnt>=minlag))
    {
      /*structure needed for mpfit*/
      struct datapoints * data = malloc(sizeof(struct datapoints));
      data->x = malloc(availcnt*sizeof(double));
      data->y = malloc(2*availcnt*sizeof(double));
      data->ey = malloc(availcnt*sizeof(double));

      /*wavelength, needed for mpfit*/
      lambda = 2.9979e8/(prm->tfreq*1.e3);

      goodcnt = 0;
      for(i=0;i<availcnt;i++)
      {
        lag = lag_avail[i];
        logpwr[goodcnt]    = log(lagpwr[lag]);
        good_lags[goodcnt] = lag;
        goodcnt++;
      }

      /*assign lag times and acf values to mpfit structure*/
      pwr = 0.0;
      for(i=0;i<goodcnt;i++)
      {
        lag = good_lags[i];
        /*tauscan AND new ROS*/
        if((prm->cp == 3310 || prm->cp == 503 || prm->cp == -503) && prm->mplgs == 18)
          L = lag;
        /*non-tauscan OR old ROS*/
        else
          for(j=0;j<mplgs;j++)
            if(abs(prm->lag[0][j]-prm->lag[1][j])==lag)
              L = j;
        re = raw->acfd[0][R*prm->mplgs+L];
        im = raw->acfd[1][R*prm->mplgs+L];

        data->x[i] = lag*prm->mpinc*1.e-6;
        data->y[i*2] = re;
        data->y[i*2+1] = im;
        exdata[i].lagnum = lag;
        exdata[i].phase = atan2(im,re)*180./PI;
        exdata[i].lagpwr = sqrt(re*re+im*im);

        /*xcf_phases[i]=atan2(raw->xcfd[R][L][1],raw->xcfd[R][L][0])*180./PI;*/
        pwr += lagpwr[lag];
      }

      /*use power ratio to weight error*/
      for(i=0;i<goodcnt;i++)
      {
        lag = good_lags[i];
        sigma[i] = pwr/exdata[i].lagpwr;
        data->ey[i] = lagpwr[lag]/pwr;
      }

      /*get velocity guess from model comparisons*/
      double model_guess = getguessex(goodcnt,mplgs,120,exdata,prm->tfreq,prm->mpinc);
      w_limit = model_guess;
      if(w_limit == -88888888.) continue;
      /*initial velocity guess in angular Doppler frequency*/
      pdouble[1] = w_limit*4.*PI/lambda;


      /* Determine lambda power and decay time initial guesses from lsfit*/
      nrfit(good_lags,logpwr,goodcnt,sigma,1,&a,&b,&siga,&sigb,&chi2,&q);
      fitted_width = -2.9979e8*b/(prm->mpinc*1.e-6)/(2*PI*1000.0*prm->tfreq);
      if(fitted_width < 0.00) fitted_width = 1.e-3;
      if(isnan(fitted_width)) fitted_width = 1.e6;
      fitted_power = log(exp(a) + skynoise);


      /**********************/
      /*single component fit*/
      /**********************/


      /*zero mpfit structures*/
      bzero(&parssingle[0], sizeof(mp_par));
      bzero(&parssingle[1], sizeof(mp_par));
      bzero(&parssingle[2], sizeof(mp_par));
      bzero(&config, sizeof(config));
      bzero(&result, sizeof(result));
      memset(&result, 0, sizeof(result));
      result.xerror = perrorsingle;


      /*initial decay time guess*/
      t_limit = lambda/(2.*PI*fitted_width);
      psingle[0] = t_limit;
      w_limit = model_guess;
      if(w_limit == -88888888.) continue;
      /*initial velocity guess in angular Doppler frequency*/
      psingle[1] = w_limit*4.*PI/lambda;

      /*lag0power initial guess*/
      psingle[2] = raw->acfd[0][R*prm->mplgs];


      /*limit values to prevent fit from going to +- inf and breaking*/
      t_limit = 999999.;
      parssingle[0].limited[0] = 1;
      parssingle[0].limits[0]  = -1.*t_limit;
      parssingle[0].limited[1] = 1;
      parssingle[0].limits[1]  = t_limit;/*

			fprintf(stderr,"%d  %lf  %lf  %lf\n",R,model_guess,psingle[1],psingle[2]);*/



      /*max iterations*/
      config.maxiter = 250;
      /*convergence criteria*/
      config.ftol = .001;
      config.nofinitecheck=0;

			if(print)
				fprintf(stdout,"%lf  %lf  %lf\n",psingle[0],psingle[1],psingle[2]);

      /*run a single-component fit*/
      status = mpfit(singlefit,availcnt,3,psingle,parssingle,&config,(void *)data,&result);

      /*final params from single-component fit*/
      t_if = psingle[0];
      f_if = psingle[1];
      lag0pwrf = psingle[2];

      /*params into velocity, w_l*/
      w_if = lambda/(2.*PI*t_if);
      v_if = lambda*f_if/(4.*PI);

      /*calculate the average acf fitting error*/
      acferr = 0.;
      for(i=0;i<goodcnt;i++)
      {
        lag = good_lags[i];
        if(tauflg && prm->mplgs == 18)
        	L = lag;
        else
          for(j=0;j<mplgs;j++)
            if(abs(prm->lag[0][j]-prm->lag[1][j])==lag)
              L = j;

        tau = lag*prm->mpinc*1.e-6;
        ref = lag0pwrf*exp(-1.0*tau/t_if)*cos(tau*f_if);
        imf = lag0pwrf*exp(-1.0*tau/t_if)*sin(tau*f_if);
        acferr += (pow(raw->acfd[0][R*prm->mplgs+L]-ref,2) + pow(raw->acfd[1][R*prm->mplgs+L]-imf,2))*lagpwr[lag]/pwr;
      }
      acferr = sqrt(acferr);

      fitted_power = 10.0*log10((lag0pwrf+skynoise)/skynoise);
      fit->rng[R].p_0   = lag0pwrf;

			/*the Hays radars are especially noisy*/
			if(prm->stid == 204 || prm->stid == 205)
				minpwr = 5.;

			sct_flg = (result.status > 0 && fitted_power > minpwr && lag0pwrf > 1.5*acferr);

			if(print)
				fprintf(stdout,"%d  %d  %d  %lf  %lf  %lf  %lf  %d\n",
									sct_flg,result.status,result.npegged,t_if,f_if,lag0pwrf,acferr,result.niter);


      /*if we have a good single component fit*/
      if(sct_flg)
      {
        fit->rng[R].v     = v_if;
        fit->rng[R].v_err = lambda*result.xerror[1]/(4.*PI);
        fit->rng[R].qflg  = 1;
        fit->rng[R].p_l   = 10.0*log10(lag0pwrf/skynoise);
        fit->rng[R].p_l_err = 0.;

        fit->rng[R].w_l   = w_if;
        fit->rng[R].w_l_err = lambda/(2.*PI*result.xerror[0]);
        fit->rng[R].nump  = goodcnt;
        fit->noise.skynoise = skynoise;

        fit->rng[R].gsct = (fabs(v_if)-(30-1./3.*fabs(w_if)) < 0);
      }
      free(data->x);
      free(data->y);
      free(data->ey);
      free(data);
    }
  }

  free(lagpwr);
  free(logpwr); 
  free(lag_avail);
  free(good_lags);
  free(sigma);
  free(exdata);
  free(badlag);

  return;
}
