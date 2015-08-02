#!/usr/bin/make -f
# -*- makefile -*-
#
# Makefile for Linux system

CC := g++
CFLAGS := -g -O2 -Wall -I.

all: Release/test

clean:
	rm -f *.o
	rm -f Release/test

TEST_OBJS = common.o dio.o synthesis.o matlabfunctions.o \
            cheaptrick.o stonemask.o d4c.o fft.o test.o

Release/test: $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS)

.cpp.o:
	$(CC) $(CFLAGS) -c $<
