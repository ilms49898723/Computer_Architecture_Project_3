/*
 * InstSimulator.hpp
 *
 *  Created on: 2016/03/11
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTSIMULATOR_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTSIMULATOR_HPP_

#include <cstdio>
#include <cstdlib>
#include <deque>
#include "InstDecoder.hpp"
#include "InstMemory.hpp"
#include "InstDataBin.hpp"
#include "InstType.hpp"

namespace inst {

class InstSimulator {
private:
    constexpr static int MAXN = 4096;

public:
    InstSimulator();

    virtual ~InstSimulator();

    void init();

    void loadImageI(const unsigned* src, const unsigned& len, const unsigned& pc);

    void loadImageD(const unsigned* src, const unsigned& len, const unsigned& sp);

    void setLogFile(FILE* snapshot, FILE* errorDump);

    void simulate();

private:
    bool alive;
    unsigned currentPc;
    unsigned originalPc;
    unsigned cycle;
    FILE* snapshot;
    FILE* errorDump;
    InstMemory memory;
    InstDataBin instList[MAXN];

private:
    void dumpSnapshot(FILE* fp);

    unsigned instMemLoad(const unsigned& addr, const InstDataBin& inst);

    void instMemStore(const unsigned& addr, const unsigned& val, const InstDataBin& inst);

    bool isNop(const InstDataBin& inst);

    bool isHalt(const InstDataBin& inst);

    bool isMemoryLoad(const InstDataBin& inst);

    bool isMemoryStore(const InstDataBin& inst);

    bool isBranch(const InstDataBin& inst);

    bool isBranchR(const InstDataBin& inst);

    bool isBranchI(const InstDataBin& inst);

    bool isBranchJ(const InstDataBin& inst);
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTSIMULATOR_HPP_ */
