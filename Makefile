#!/usr/bin/make -f
# -*- makefile -*-
#
# Makefile for Linux system

CC := g++
AR := ar
CFLAGS := -g -O2 -Wall -I. -fPIC

all: Release/test Release/libworld.a

clean:
	rm -rf *.o
	rm -f Release/*

TEST_OBJS = common.o dio.o synthesis.o matlabfunctions.o \
            cheaptrick.o stonemask.o d4c.o fft.o test.o

Release/test: $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS)

Release/libworld.a: $(TEST_OBJS)
	$(AR) rvs Release/libworld.a $(TEST_OBJS)

test.cpp: d4c.h dio.h matlabfunctions.h cheaptrick.h stonemask.h synthesis.h
synthesis.cpp: synthesis.h common.h constantnumbers.h matlabfunctions.h
matlabfunctions.cpp: matlabfunctions.h constantnumbers.h
fft.cpp: fft.h
dio.cpp: dio.h common.h constantnumbers.h matlabfunctions.h
d4c.cpp: d4c.h common.h constantnumbers.h matlabfunctions.h
common.cpp: common.h constantnumbers.h matlabfunctions.h
cheaptrick.cpp: cheaptrick.h common.h constantnumbers.h matlabfunctions.h
matlabfunctions.h: common.h
common.h: fft.h

.cpp.o:
	$(CC) $(CFLAGS) -c $<

