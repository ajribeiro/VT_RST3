# makefile for fit_lib
#
#
include $(MAKECFG).$(SYSTEM)



INCLUDE= -I$(IPATH)/base -I$(IPATH)/general  -I$(IPATH)/superdarn/fit -I$(IPATH)/superdarn
SRC = acf_preproc.c acf_preproc.h dbl_cmp.c dbl_cmp.h elevation.c elevation.h \
      elev_goose.c elev_goose.h \
      omega_guess.c omega_guess.h ground_scatter.c ground_scatter.h \
      more_badlags.c more_badlags.h  badlags.c\
      badlags_s.c calc_phi_res.c calc_phi_res.h \
      rang_badlags.c rang_badlags.h noise_stat.c noise_stat.h \
      fit_acf2.c fit_acf2.h \
       do_fit2.c do_phase_fit.c do_phase_fit.h fitacf2.c fitacfversion.h
OBJS = acf_preproc.o dbl_cmp.o elevation.o elev_goose.o \
       omega_guess.o ground_scatter.o more_badlags.o badlags.o badlags_s.o \
       calc_phi_res.o \
       rang_badlags.o noise_stat.o fit_acf2.o \
       do_fit2.o do_phase_fit.o fitacf2.o
INC=$(IPATH)/superdarn
DSTPATH=$(LIBPATH)
OUTPUT=fitacf2
LINK="1"



include $(MAKELIB).$(SYSTEM)
