# makefile for Computer_Architecture_Project_3

CC := g++

CXXFLAGS := -std=c++11 -Os -Wall -Wextra

OBJS := InstDataBin.o \
        InstDataStr.o \
        InstDecoder.o \
        InstImageReader.o \
        InstLookUp.o \
        InstMemory.o \
        InstRegister.o \
        InstSimulator.o \
        InstUtility.o \
        main.o

OUTPUT := CMP

.SUFFIXS:
.SUFFIXS: .cpp .o

.PHONY: all CMP clean

all: CMP

CMP: ${OBJS}
	${CC} ${CXXFLAGS} -o $@ ${OBJS}

.cpp.o:
	${CC} ${CXXFLAGS} -c $<

clean:
	-rm -f ${OBJS} ${OUTPUT}
