# Makefile for rtcsd
# ==================
# Author: R.J.Barnes
# by R.J.Barnes
#
#
include $(MAKECFG).$(SYSTEM)
INCLUDE=-I$(IPATH)/base -I$(IPATH)/general -I$(IPATH)/superdarn \
        -DPOSIX -D__EXTENSIONS__

OBJS=loginfo.o rtcfit.o
SRC=hlpstr.h errstr.h rtcfit.c loginfo.c loginfo.h
LIBS=-lfitcnx.1 -lcnx.1 -lcfit.1 -lfit.1 -lrscan.1 -lradar.1 -ldmap.1 -lrtime.1 -lopt.1 -lrcnv.1  
SLIB=-lm -lz

ifdef TCPIPLIBS
  SLIB=-lm -lz $(TCPIPLIBS) 
DSTPATH = $(BINPATH)
OUTPUT = rtcfit
endif

include $(MAKEBIN).$(SYSTEM)
