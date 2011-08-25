# Makefile for radar library
# ========================
# by R.J.Barnes
#
#
include $(MAKECFG).$(SYSTEM)
INCLUDE=-I$(IPATH)/base -I$(IPATH)/general -I$(IPATH)/superdarn
SRC=mergewrite.c mergeread.c
OBJS = mergewrite.o mergeread.o
INC=$(IPATH)/superdarn
DSTPATH=$(LIBPATH)
OUTPUT = merge
LINK="1"



include $(MAKELIB).$(SYSTEM)
