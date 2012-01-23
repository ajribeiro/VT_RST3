
/* lmfit2.c
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
#include "lmfit2.h"
#include "badsmp.h"
#include "badlags.h"
#include "mpfit.h"


int singlefit2(int m, int n, double *p, double *deviates,
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
    re=y[i];
    sig=ey[i];
    ti=p[0];
    wi=p[1];
    lag0mag = p[2];
	
		if(i < m/2)
			deviates[i] = re-lag0mag*exp(-1.*tau/ti)*cos(wi*tau);
		else
			deviates[i] = re-lag0mag*exp(-1.*tau/ti)*sin(wi*tau);
  }

  return 0;
}

void lmfit2(struct RadarParm *prm,struct RawData *raw,
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

	prm->noise.mean = skynoise;

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

		/*not tauscan, check for badlags*/
		if(!tauflg) FitACFCkRng(R+1,badlag,&badsmp,&fblk->prm);

		/*Preliminaries, badlag checking, power level checking*/
		for(L=0;L<mplgs;L++)
		{
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
      data->x = malloc(availcnt*2*sizeof(double));
      data->y = malloc(2*availcnt*sizeof(double));
      data->ey = malloc(availcnt*2*sizeof(double));

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
				data->x[i+goodcnt] = lag*prm->mpinc*1.e-6;
        data->y[i] = re;
        data->y[i+goodcnt] = im;

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
        data->ey[i] = exdata[i].lagpwr/pwr;
				data->ey[i+goodcnt] = exdata[i].lagpwr/pwr;
      }

      /*get velocity guess from model comparisons*/
      double model_guess = getguessex(prm,raw,fit,fblk,R,skynoise);
      w_limit = model_guess;
      if(w_limit == -88888888.) continue;
      /*initial velocity guess in angular Doppler frequency*/
      pdouble[1] = w_limit*4.*PI/lambda;


      /* Determine lambda power and decay time initial guesses from lsfit*/
      nrfit(good_lags,logpwr,goodcnt,sigma,1,&a,&b,&siga,&sigb,&chi2,&q);
      fitted_width = -2.9979e8*b/(prm->mpinc*1.e-6)/(2*PI*1000.0*prm->tfreq);
      if(fitted_width < 0.00) fitted_width = 1.e-3;
      if(isnan(fitted_width)) fitted_width = 1.e3;
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
      parssingle[0].limits[0]  = 1e-3;
      parssingle[0].limited[1] = 1;
      parssingle[0].limits[1]  = 1000.;/*

			fprintf(stderr,"%d  %lf  %lf  %lf\n",R,model_guess,psingle[1],psingle[2]);*/



      /*max iterations*/
      config.maxiter = 200;
      /*convergence criteria*/
      config.ftol = .0001;
			config.gtol = .0001;
      config.nofinitecheck=0;


			if(print)
				fprintf(stdout,"%lf  %lf  %lf\n",psingle[0],psingle[1],psingle[2]);

      /*run a single-component fit*/
      status = mpfit(singlefit2,availcnt*2,3,psingle,parssingle,&config,(void *)data,&result);

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


			sct_flg = (result.status > 0 && fitted_power > minpwr && lag0pwrf > 1.5*acferr && result.npegged == 0);

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
