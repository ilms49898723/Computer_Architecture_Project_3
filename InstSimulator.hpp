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
#include "InstDataBin.hpp"
#include "InstDecoder.hpp"
#include "InstMemory.hpp"
#include "InstRegister.hpp"
#include "InstPageTable.hpp"
#include "InstTLB.hpp"
#include "InstType.hpp"
#include "InstCache.hpp"

namespace inst {

/**
 * Simulator
 */
class InstSimulator {
private:
    constexpr static int MAXN = 4096;

public:
    /**
     * Default constructor
     */
    InstSimulator();

    /**
     * Default destructor
     */
    virtual ~InstSimulator();

    /**
     * Initialize
     */
    void init();

    /**
     * Load iimage.bin
     *
     * @param src pointer to instruction data
     * @param len length of src
     * @param pc initial pc
     */
    void loadInstruction(const unsigned* src, const unsigned len, const unsigned pc);

    /**
     * Load dimage.bin
     *
     * @param src pointer to data
     * @param len length of src
     * @param sp initial sp
     */
    void loadData(const unsigned* src, const unsigned len, const unsigned sp);

    /**
     * Set property(command-line arguments)
     *
     * @param iMemArgu i-memory parameters
     * @param dMemArgu d-memory parameters
     */
    void setProperty(const InstParameter& iMemArgu, const InstParameter& dMemArgu);

    /**
     * Set log file(snapshot, report)
     *
     * @param snapshot snapshot filename
     * @param report report filename
     */
    void setLogFile(const std::string& snapshot, const std::string& report);

    /**
     * Start simulate
     */
    void start();

private:
    void dumpSnapshot(FILE* fp) const;

    unsigned instMemLoad(const unsigned addr, const InstDataBin& inst) const;

    void instMemStore(const unsigned addr, const unsigned val, const InstDataBin& inst);

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
    unsigned originalPc;
    unsigned currentPc;
    unsigned cycle;

private:
    FILE* snapshot;
    FILE* report;

private:
    InstDataBin instructionSet[MAXN];
    InstRegister reg;
    InstMemory memory;
    InstMemory instruction;
    InstPageTable iPageTable;
    InstPageTable dPageTable;
    InstTLB iTLB;
    InstTLB dTLB;
    InstCache iCache;
    InstCache dCache;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTSIMULATOR_HPP_ */
