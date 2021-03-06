# makefile for Computer_Architecture_Project_3

CC := g++

CXXFLAGS := -std=c++11 -Os -Wall -Wextra

OBJS := InstCache.o \
        InstDataBin.o \
        InstDataStr.o \
        InstDecoder.o \
        InstDisk.o \
        InstImageReader.o \
        InstLookUp.o \
        InstMemory.o \
        InstPageTable.o \
        InstRegister.o \
        InstSimulator.o \
        InstTLB.o \
        InstUtility.o \
        main.o

OUTPUT := CMP

.SUFFIXS:
.SUFFIXS: .cpp .o

.PHONY: all CMP testGen help clean

all: CMP

CMP: ${OBJS}
	${CC} ${CXXFLAGS} -o $@ ${OBJS}

testGen: testGenerator.cpp
	${CC} ${CXXFLAGS} -o $@ $<

.cpp.o:
	${CC} ${CXXFLAGS} -c $<

help:
	@echo '"make" to build CMP'
	@echo '"make testGen" to build testGenerator'
	@echo '"make clean" to clean working directory'

clean:
	-rm -f ${OBJS} ${OUTPUT} testGen

