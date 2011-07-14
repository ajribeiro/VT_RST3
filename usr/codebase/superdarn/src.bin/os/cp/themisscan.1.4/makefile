# Makefile for themisscan
# =======================
# by R.J.Barnes
#
#

include $(MAKECFG).$(SYSTEM)



INCLUDE=-I$(IPATH)/base -I$(IPATH)/general -I$(IPATH)/superdarn \
        -I$(USR_IPATH)/superdarn
OBJS = themisscan.o
SRC=themisscan.c
DSTPATH = $(USR_BINPATH)
OUTPUT = themisscan
LIBS= -lsite.1 -lsite.fhe.1 -lsite.fhw.1 -lsite.tst.1 -lradarshell.1 -lshmem.1 -lops.1 -lrmsgsnd.1 -ltcpipmsg.1 -lerrlog.1 -lfreq.1 -lacfex.1 -lacf.1 -lfit.1 -lraw.1 -lfitacf.1 -lcfit.1 -lrscan.1 -liqdata.1 -ltsg.1 -lradar.1 -ldmap.1 -lopt.1 -lrtime.1 -lrcnv.1  

ifeq ($(SYSTEM),linux)
  SLIB=-lm -lrt -lz
else
  SLIB=-lm -lz
endif

include $(MAKEBIN).$(SYSTEM)
