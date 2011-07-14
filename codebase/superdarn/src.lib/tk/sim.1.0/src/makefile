# Makefile for sim library
# ========================
# by R.J.Barnes
#
#
include $(MAKECFG).$(SYSTEM)
INCLUDE=-I$(IPATH)/base -I$(IPATH)/general -I$(IPATH)/superdarn
SRC=sim.c simread.c simwrite.c
OBJS = sim.o simread.o simwrite.o
INC=$(IPATH)/superdarn
DSTPATH=$(LIBPATH)
OUTPUT = sim
LINK="1"



include $(MAKELIB).$(SYSTEM)
