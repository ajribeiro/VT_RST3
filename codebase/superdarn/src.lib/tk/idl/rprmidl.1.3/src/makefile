# Makefile for rprmidl library
# ============================
# by R.J.Barnes
#
#
include $(MAKECFG).$(SYSTEM)

INCLUDE=-I$(IPATH)/base -I$(IPATH)/general -I$(IPATH)/superdarn -I${IDL_IPATH}

SRC=rprmidl.c
OBJS = rprmidl.o
INC=$(IPATH)/superdarn
DSTPATH=$(LIBPATH)
OUTPUT = rprmidl
LINK="1"

include $(MAKELIB).$(SYSTEM)
