
/* lmfit_test.c
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
#include "lmfit_test.h"
#include "badsmp.h"
#include "badlags.h"
#include "mpfit.h"



void lmfit_test(struct RadarParm *prm,struct RawData *raw,
              struct FitData *fit, struct FitBlock *fblk)
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
  int   lastlag,lag,i,j,R,L;
  double nonzeronoise,acferr;

  /*variable needed for mpfit call*/
  mp_par    parsdouble[6];
  mp_par    parssingle[3];
  mp_result result;
  mp_config config;
  double pdouble[6];
  double psingle[3];
  double w_limit,t_limit,t_if,w_if,lag0pwrf,v_if,f_if,lambda,tau,ref,imf;
  int status;
  double perrordouble[6];
  double perrorsingle[3];
  float *sigma = malloc(prm->mplgs*sizeof(double));
  struct exdatapoints * exdata = malloc(prm->mplgs*sizeof(struct exdatapoints));


  int print=0;

  int *badlag = malloc(prm->mplgs * sizeof(int));
  struct FitACFBadSample badsmp;


  /* Find the highest lag, and allocate memory */
  if(!((prm->cp == 3310 || prm->cp == 503 || prm->cp == -503) && prm->mplgs == 18))
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
  if (fblk->prm.xcf)
  {
   FitSetXrng(fit,fblk->prm.nrang);
   FitSetElv(fit,fblk->prm.nrang);
  }

  /*calculate noise levels*/
  lm_noise_stat(prm,raw,&skynoise,&nonzeronoise);
  if(prm->cp != 3310 && prm->cp != 503 && prm->cp != -503)
  {
    if(fblk->prm.channel==0) FitACFBadlags(&fblk->prm,&badsmp);
    else FitACFBadlagsStereo(&fblk->prm,&badsmp);
  }


  print=0.;
  /* Loop every range gate and calculate parameters */
	fprintf(stdout,"%d  %d  %lf  %d  %lf\n",prm->nrang,prm->mplgs,skynoise,prm->tfreq,prm->mpinc*1.e-6);
	fprintf(stdout,"%d  %d  %d  %d  %d  %d  %d  %d\n",prm->stid,prm->time.yr,prm->time.mo,
									prm->time.dy,prm->time.hr,prm->time.mt,(int)prm->time.sc,prm->bmnum);
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
    fit->rng[R].gsct     = 0;
    availcnt = 0;

    /*calculate SNR of lag0power*/
    lag0pwr  = 10.0*log10((raw->acfd[0][R*prm->mplgs]+skynoise)/skynoise);

    fprintf(stdout,"%d\n",R);

    /*tauscan, new ROS version*/
    if((prm->cp == 3310 || prm->cp == 503 || prm->cp == -503) && prm->mplgs == 18)
    {
      for (L=0;L<prm->mplgs;L++)
      {
        lag = L;
        re  = raw->acfd[0][R*prm->mplgs+L];
        im  = raw->acfd[1][R*prm->mplgs+L];
        lagpwr[lag] = sqrt(re*re + im*im);
        if(lagpwr[lag]>raw->acfd[0][R*prm->mplgs]/sqrt(1.0*prm->nave))
        {
            lag_avail[availcnt] = lag;
            availcnt++;
        }
        else lagpwr[lag] = 0.0;
        fprintf(stdout,"%d  %lf  %lf  %d\n",lag,raw->acfd[0][R*prm->mplgs+L],raw->acfd[1][R*prm->mplgs+L],
																						(lagpwr[lag]>raw->acfd[0][R*prm->mplgs]/sqrt(1.0*prm->nave)));
      }
      pwr_flg = (lag0pwr>=minpwr);
    }
    /*tauscan, old ROS version (lag power checking, no badlag checking, SNR checking)*/
    else if(prm->cp == 3310 || prm->cp == 503 || prm->cp == -503)
    {
      for (L=0;L<prm->mplgs;L++)
      {
        lag = abs(prm->lag[0][L] - prm->lag[1][L]);
        re  = raw->acfd[0][R*prm->mplgs+L];
        im  = raw->acfd[1][R*prm->mplgs+L];
        lagpwr[lag] = sqrt(re*re + im*im);
        if(lagpwr[lag]>raw->acfd[0][R*prm->mplgs]/sqrt(1.0*prm->nave))
        {
          lag_avail[availcnt] = lag;
          availcnt++;
        }
        else lagpwr[lag] = 0.0;
        fprintf(stdout,"%d  %lf  %lf  %d\n",lag,raw->acfd[0][R*prm->mplgs+L],raw->acfd[1][R*prm->mplgs+L],
																								(lagpwr[lag]>raw->acfd[0][R*prm->mplgs]/sqrt(1.0*prm->nave)));
      }
      pwr_flg = (lag0pwr>=minpwr);
    }
    /*non-tauscan operation (lag power checking, badlag checking, SNR checking)*/
    else
    {
      FitACFCkRng(R+1,badlag,&badsmp,&fblk->prm);
      for (L=0;L<prm->mplgs;L++)
      {
        lag = abs(prm->lag[0][L] - prm->lag[1][L]);
        re  = raw->acfd[0][R*prm->mplgs+L];
        im  = raw->acfd[1][R*prm->mplgs+L];
        lagpwr[lag] = sqrt(re*re + im*im);
        if(badlag[L])
          availflg = 0;
        else
          availflg = 1;
        if(availflg && lagpwr[lag]>raw->acfd[0][R*prm->mplgs]/sqrt(1.0*prm->nave))
        {
          lag_avail[availcnt] = lag;
          availcnt++;
        }
        else lagpwr[lag] = 0.0;
        fprintf(stdout,"%d  %lf  %lf  %d\n",lag,raw->acfd[0][R*prm->mplgs+L],raw->acfd[1][R*prm->mplgs+L],
																						(availflg && lagpwr[lag]>raw->acfd[0][R*prm->mplgs]/sqrt(1.0*prm->nave)));
      }
      pwr_flg = raw->acfd[0][R*prm->mplgs]>=skynoise;
      minlag = 4;
    }
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
          for(j=0;j<prm->mplgs;j++)
            if(abs(prm->lag[0][L]-prm->lag[1][L])==lag)
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


      /*zero out mpfit structures*/
      bzero(&parsdouble[0], sizeof(mp_par));
      bzero(&parsdouble[1], sizeof(mp_par));
      bzero(&parsdouble[2], sizeof(mp_par));
      bzero(&parsdouble[3], sizeof(mp_par));
      bzero(&parsdouble[4], sizeof(mp_par));
      bzero(&parsdouble[5], sizeof(mp_par));
      bzero(&config, sizeof(config));
      bzero(&result, sizeof(result));
      memset(&result, 0, sizeof(result));
      result.xerror = perrordouble;


      /*get velocity guess from model comparisons*/
      double model_guess = getguessex(goodcnt,prm->mplgs,120,exdata,prm->tfreq,prm->mpinc);
      w_limit = model_guess;
      if(w_limit == -88888888.) continue;
      /*initial velocity guess in angular Doppler frequency*/
      pdouble[1] = w_limit*4.*PI/lambda;




      /* Determine lambda power and decay time initial guesses from lsfit*/
      nrfit(good_lags,logpwr,goodcnt,sigma,1,&a,&b,&siga,&sigb,&chi2,&q);
      fitted_width = -2.9979e8*b/(prm->mpinc*1.e-6)/(2*PI*1000.0*prm->tfreq);
      if(fitted_width < 0.00) fitted_width = 1.e-3;
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

      /*same limit as before, same reason*/
      t_limit = -999999.;
      parssingle[0].limited[0] = 1;
      parssingle[0].limits[0]  = t_limit;
      t_limit = 999999.;
      parssingle[0].limited[1] = 1;
      parssingle[0].limits[1]  = t_limit;


      /*max iterations*/
      config.maxiter = 250;
      /*convergence criteria*/
      config.ftol = .001;
      config.nofinitecheck=0;

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
        if((prm->cp == 3310 || prm->cp == 503 || prm->cp == -503) && prm->mplgs == 18)
        	L = lag;
        else
          for(j=0;j<prm->mplgs;j++)
            if(abs(prm->lag[0][L]-prm->lag[1][L])==lag)
              L = j;

        tau = lag*prm->mpinc*1.e-6;
        ref = lag0pwrf*exp(-1.0*tau/t_if)*cos(tau*f_if);
        imf = lag0pwrf*exp(-1.0*tau/t_if)*sin(tau*f_if);
        acferr += (pow(raw->acfd[0][R*prm->mplgs+L]-ref,2) + pow(raw->acfd[1][R*prm->mplgs+L]-imf,2))*lagpwr[lag]/pwr;
      }
      acferr = sqrt(acferr);


      fitted_power = 10.0*log10((lag0pwrf+skynoise)/skynoise);
      fit->rng[R].p_0   = lag0pwrf;

			fprintf(stdout,"%d  %d  %d  %lf  %lf  %lf  %lf  %d\n",
				(result.status > 0 && fitted_power > minpwr && lag0pwrf > 2.*acferr),
				result.status,result.npegged,t_if,f_if,lag0pwrf,acferr,result.niter);

			
      /*if we have a good single component fit*/
      if(result.status > 0 && fitted_power > minpwr && lag0pwrf > 2.*acferr/* && result.npegged == 0*/)
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
