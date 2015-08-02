#!/usr/bin/make -f
# -*- makefile -*-
#
# Makefile for Linux system

CC := g++
AR := ar
MKOCTFILE := mkoctfile
CFLAGS := -g -O2 -Wall -I. -fPIC

all: Release/test

clean:
	rm -rf *.o
	rm -f Release/*

TEST_OBJS = common.o dio.o synthesis.o matlabfunctions.o \
            cheaptrick.o stonemask.o d4c.o fft.o test.o

Release/test: $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS)

.cpp.o:
	$(CC) $(CFLAGS) -c $<


