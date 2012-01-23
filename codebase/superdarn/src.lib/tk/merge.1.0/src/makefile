# Makefile for radar library
# ========================
# by R.J.Barnes
#
#
include $(MAKECFG).$(SYSTEM)
INCLUDE=-I$(IPATH)/base -I$(IPATH)/general -I$(IPATH)/superdarn
SRC=mergeread.c mergewrite.c
OBJS = mergeread.o mergewrite.o
INC=$(IPATH)/superdarn
DSTPATH=$(LIBPATH)
OUTPUT = merge
LINK="1"



include $(MAKELIB).$(SYSTEM)
