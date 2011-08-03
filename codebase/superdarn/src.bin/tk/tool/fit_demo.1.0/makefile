# Makefile for fit_demo
# ======================
# Author: R.J.Barnes
# by R.J.Barnes
#
#
include $(MAKECFG).$(SYSTEM)

INCLUDE=-I$(IPATH)/base -I$(IPATH)/general -I$(IPATH)/superdarn
OBJS = fit_demo.o
SRC=fit_demo.c
DSTPATH = $(BINPATH)
OUTPUT = fit_demo
LIBS=-loldfit.1 -lrpos.1 -lfit.1 -lrscan.1 -lradar.1 -ldmap.1 -lopt.1 -lrtime.1 -lrcnv.1 -laacgm.1 -ligrf.1
SLIB=-lm -lz


include $(MAKEBIN).$(SYSTEM)
