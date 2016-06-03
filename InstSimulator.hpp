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
#include "InstDisk.hpp"
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
    ~InstSimulator();

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
    void setProperty(const InstParameter& iParam, const InstParameter& dParam);

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

    void dumpCMP(FILE* fp) const;

    void search(const unsigned virtualAddr, const InstRoute route);

    unsigned instALUR(const InstDataBin& inst);

    unsigned instALUI(const InstDataBin& inst);

    bool isNop(const InstDataBin& inst) const;

    bool isHalt(const InstDataBin& inst) const;

    bool isMemoryLoad(const InstDataBin& inst) const;

    bool isMemoryStore(const InstDataBin& inst) const;

    bool isBranchR(const InstDataBin& inst) const;

    bool isBranchI(const InstDataBin& inst) const;

private:
    unsigned originalPc;
    unsigned currentPc;
    unsigned cycle;

private:
    FILE* snapshot;
    FILE* report;

private:
    InstRegister reg;
    InstParameter iParam;
    InstParameter dParam;
    InstTLB iTLB;
    InstTLB dTLB;
    InstPageTable iPageTable;
    InstPageTable dPageTable;
    InstMemory iMemory;
    InstMemory dMemory;
    InstCache iCache;
    InstCache dCache;
    InstDisk iDisk;
    InstDisk dDisk;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTSIMULATOR_HPP_ */
