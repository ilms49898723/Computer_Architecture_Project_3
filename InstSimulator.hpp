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
#include "InstRegister.hpp"
#include "InstDataBin.hpp"
#include "InstType.hpp"

namespace inst {

/**
 * Simulator
 */
class InstSimulator {
private:
    constexpr static int MAXN = 4096;

public:
    InstSimulator();

    virtual ~InstSimulator();

    void init();

    void loadImageI(const unsigned* src, const unsigned& len, const unsigned& pc);

    void loadImageD(const unsigned* src, const unsigned& len, const unsigned& sp);

    void setLogFile(FILE* snapshot, FILE* report);

    void simulate();

private:
    void dumpSnapshot(FILE* fp) const;

    unsigned instMemLoad(const unsigned& addr, const InstDataBin& inst) const;

    void instMemStore(const unsigned& addr, const unsigned& val, const InstDataBin& inst);

    bool isNop(const InstDataBin& inst) const;

    bool isHalt(const InstDataBin& inst) const;

    bool isMemoryLoad(const InstDataBin& inst) const;

    bool isMemoryStore(const InstDataBin& inst) const;

    bool isBranch(const InstDataBin& inst) const;

    bool isBranchR(const InstDataBin& inst) const;

    bool isBranchI(const InstDataBin& inst) const;

    bool isBranchJ(const InstDataBin& inst) const;

private:
    bool alive;
    unsigned currentPc;
    unsigned originalPc;
    unsigned cycle;
    FILE* snapshot;
    FILE* report;
    InstRegister reg;
    InstMemory mem;
    InstDataBin instList[MAXN];
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTSIMULATOR_HPP_ */
