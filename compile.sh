#!/bin/bash

#g++ `wx-config --cxxflags` -o wxMinimal *.cpp `wx-config --libs`
#if [ $? -eq 0 ]; then
#	./wxMinimal
#fi

gcc -o ViPlex-stat ViPlex-stat.c -l sqlite3
