# Makefile for fitidl library
# ===========================
# by R.J.Barnes
#
#
include $(MAKECFG).$(SYSTEM)

INCLUDE=-I$(IPATH)/base -I$(IPATH)/general -I$(IPATH)/superdarn -I${IDL_IPATH}

SRC=fitidl.c
OBJS = fitidl.o
INC=$(IPATH)/superdarn
DSTPATH=$(LIBPATH)
OUTPUT = fitidl
LINK="1"

include $(MAKELIB).$(SYSTEM)
