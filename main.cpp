/*
 * main.cpp
 *
 *  Created on: 2016/03/08
 *      Author: LittleBird
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include "InstType.hpp"
#include "InstSimulator.hpp"
#include "InstImageReader.hpp"

int main(const int argc, const char** argv) {
    // constant string filename
    const std::string iimageFilename = "iimage.bin";
    const std::string dimageFilename = "dimage.bin";
    const std::string snapshotFilename = "snapshot.rpt";
    const std::string reportFilename = "report.rpt";
    inst::InstParameter iMemArgs, dMemArgs;
    inst::parseArgument(iMemArgs, dMemArgs, argc, argv);
    // load iimage, dimage
    unsigned pc, sp;
    unsigned instructions[2048], memory[2048];
    unsigned iLen = inst::InstImageReader::readInstImage(iimageFilename.c_str(), instructions, &pc);
    unsigned dLen = inst::InstImageReader::readDataImage(dimageFilename.c_str(), memory, &sp);
    // set simulator, start simulation
    inst::InstSimulator simulator;
    simulator.setProperty(argc, argv);
    simulator.setLogFile(snapshotFilename,reportFilename);
    simulator.loadInstruction(instructions, iLen, pc);
    simulator.loadData(memory, dLen, sp);
    simulator.simulate();
    return 0;
}
