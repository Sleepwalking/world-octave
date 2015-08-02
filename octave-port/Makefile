#!/usr/bin/make -f
# -*- makefile -*-
#
# Makefile for Linux system

CC := g++
AR := ar
MKOCTFILE := mkoctfile
CFLAGS := -g -O2 -Wall -I. -fPIC

all: ../Release/dio.oct ../Release/stonemask.oct ../Release/cheaptrick.oct \
      ../Release/d4c.oct ../Release/world_synth.oct
clean:
	rm -rf *.o
	rm -f ../Release/*

TEST_OBJS = ../common.o ../dio.o ../synthesis.o ../matlabfunctions.o \
            ../cheaptrick.o ../stonemask.o ../d4c.o ../fft.o ../test.o

../Release/test: $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS)

../Release/libworld.a: $(TEST_OBJS)
	$(AR) rvs ../Release/libworld.a $(TEST_OBJS)

../Release/%.oct: ../Release/libworld.a %.cc
	$(MKOCTFILE) $*.cc -lworld -L../Release -o ../Release/$*.oct

.cpp.o:
	$(CC) $(CFLAGS) -c $<


