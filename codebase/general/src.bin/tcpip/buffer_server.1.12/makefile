# Makefile for buffer_server
# ==========================
# Author: R.J.Barnes
# by R.J.Barnes
#
#
include $(MAKECFG).$(SYSTEM)
INCLUDE=-I$(IPATH)/base
SRC=hlpstr.h errstr.h buffer_server.c config.h
OBJS=buffer_server.o
DSTPATH = $(BINPATH)

LIBS=-lopt.1
ifdef TCPIPLIBS
  OUTPUT=buffer_server
endif

include $(MAKEBIN).$(SYSTEM)
