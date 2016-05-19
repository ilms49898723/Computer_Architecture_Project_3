/*
 * main.cpp
 *
 *  Created on: 2016/03/08
 *      Author: LittleBird
 */

#include <cstdio>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <string>
#include "InstSimulator.hpp"
#include "InstImageReader.hpp"

int main(const int argc, const char** argv) {
    // constant string filename
    const std::string iimageFilename = "iimage.bin";
    const std::string dimageFilename = "dimage.bin";
    const std::string snapshotFilename = "snapshot.rpt";
    const std::string reportFilename = "report.rpt";
    // load iimage, dimage
    unsigned pc, sp;
    unsigned instructions[2048], memory[2048];
    unsigned iLen = inst::InstImageReader::readImageI(iimageFilename.c_str(), instructions, &pc);
    unsigned dLen = inst::InstImageReader::readImageD(dimageFilename.c_str(), memory, &sp);
    // open output file
    FILE* snapShot;
    FILE* errorDump;
    snapShot = fopen(snapshotFilename.c_str(), "w");
    if (!snapShot) {
        fprintf(stderr, "%s: %s\n", snapshotFilename.c_str(), strerror(errno));
        exit(EXIT_FAILURE);
    }
    errorDump = fopen(reportFilename.c_str(), "w");
    if (!errorDump) {
        fprintf(stderr, "%s: %s\n", reportFilename.c_str(), strerror(errno));
        exit(EXIT_FAILURE);
    }
    // set simulator, start simulation
    inst::InstSimulator simulator;
    simulator.setProperty(argc, argv);
    simulator.setLogFile(snapShot, errorDump);
    simulator.loadImageI(instructions, iLen, pc);
    simulator.loadImageD(memory, dLen, sp);
    simulator.simulate();
    fclose(snapShot);
    fclose(errorDump);
    return 0;
}
