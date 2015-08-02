#!/usr/bin/make -f
# -*- makefile -*-
#
# Makefile for Linux system

MKOCTFILE := mkoctfile
OCTFLAGS := -s

all: ../Release/dio.oct ../Release/stonemask.oct ../Release/cheaptrick.oct \
      ../Release/d4c.oct ../Release/world_synth.oct

clean:
	rm -rf *.o
	rm -f ../Release/*

../Release/%.oct: ../Release/libworld.a %.cc
	$(MKOCTFILE) $*.cc -lworld -L../Release -o ../Release/$*.oct $(OCTFLAGS)

