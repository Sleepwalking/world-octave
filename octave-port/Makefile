#!/usr/bin/make -f
# -*- makefile -*-
#
# Makefile for Linux system

CC := g++
AR := ar
MKOCTFILE := mkoctfile
CFLAGS := -g -O2 -Wall -I. -fPIC

all: ../Release/dio.oct

clean:
	rm -rf *.o
	rm -f ../Release/*

TEST_OBJS = ../common.o ../dio.o ../synthesis.o ../matlabfunctions.o \
            ../cheaptrick.o ../stonemask.o ../d4c.o ../fft.o ../test.o

../Release/test: $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS)

../Release/libworld.a: $(TEST_OBJS)
	$(AR) rvs ../Release/libworld.a $(TEST_OBJS)

../Release/dio.oct: ../Release/libworld.a dio.cc
	$(MKOCTFILE) dio.cc -lworld -L../Release -o ../Release/dio.oct

.cpp.o:
	$(CC) $(CFLAGS) -c $<


