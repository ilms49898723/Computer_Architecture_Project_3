/*
 * InstSimulator.cpp
 *
 *  Created on: 2016/03/11
 *      Author: LittleBird
 */

#include "InstSimulator.hpp"

namespace inst {

InstSimulator::InstSimulator() {
    init();
}

InstSimulator::~InstSimulator() {

}

void InstSimulator::init() {
    reg.init();
    memory.init();
    originalPc = 0u;
    snapshot = nullptr;
    report = nullptr;
    for (int i = 0; i < InstSimulator::MAXN; ++i) {
        instruction.setData(static_cast<unsigned>(i << 2), 0, 4);
        instructionSet[i] = InstDecoder::decodeInstBin(0u);
    }
}

void InstSimulator::loadInstruction(const unsigned* src, const unsigned len, const unsigned pc) {
    this->originalPc = pc;
    for (unsigned i = 0; i < len; ++i) {
        instruction.setData(pc + (i << 2), src[i], 4);
        instructionSet[(pc >> 2) + i] = InstDecoder::decodeInstBin(src[i]);
    }
}

void InstSimulator::loadData(const unsigned* src, const unsigned len, const unsigned sp) {
    reg.setRegister(29, sp, InstSize::WORD);
    for (unsigned i = 0; i < len; ++i) {
        memory.setData(i * 4, src[i], 4);
    }
}

void InstSimulator::setProperty(const InstParameter& iMemArgu, const InstParameter& dMemArgu) {
    iPageTable.init(iMemArgu.pageSize);
    dPageTable.init(dMemArgu.pageSize);
    iTLB.init(iPageTable.entry() >> 2);
    dTLB.init(dPageTable.entry() >> 2);
    iCache.init(iMemArgu.cacheSize, iMemArgu.cacheBlockSize, iMemArgu.cacheSetAssociativity);
    dCache.init(dMemArgu.cacheSize, dMemArgu.cacheBlockSize, dMemArgu.cacheSetAssociativity);
}

void InstSimulator::setLogFile(const std::string& snapshotFilename, const std::string& reportFilename) {
    this->snapshot = fopen(snapshotFilename.c_str(), "w");
    if (!this->snapshot) {
        fprintf(stderr, "%s: %s\n", snapshotFilename.c_str(), strerror(errno));
        exit(EXIT_FAILURE);
    }
    this->report = fopen(reportFilename.c_str(), "w");
    if (!this->report) {
        fprintf(stderr, "%s: %s\n", reportFilename.c_str(), strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void InstSimulator::start() {
    if (!snapshot || !report) {
        fprintf(stderr, "Can\'t open output files\n");
        return;
    }
    currentPc = originalPc;
    cycle = 0u;
    alive = true;
    // TODO instruction fetch
    while (true) {
        if (!alive) {
            break;
        }
        dumpSnapshot(snapshot);
        ++cycle;
        currentPc += 4;
    }
    fclose(snapshot);
    fclose(report);
}

void InstSimulator::dumpSnapshot(FILE* fp) const {
    // TODO missing information
    fprintf(fp, "cycle %u\n", cycle);
    for (unsigned i = 0; i < 32; ++i) {
        fprintf(fp, "$%02d: 0x%08X\n", i, reg.getRegister(i));
    }
    fprintf(fp, "PC: 0x%08X\n", currentPc);
}

unsigned InstSimulator::instMemLoad(const unsigned addr, const InstDataBin& inst) const {
    switch (inst.getOpCode()) {
        case 0x23u:
            return memory.getData(addr, InstSize::WORD);
        case 0x21u:
            return toUnsigned(toSigned(memory.getData(addr, InstSize::HALF), InstSize::HALF));
        case 0x25u:
            return memory.getData(addr, InstSize::HALF);
        case 0x20u:
            return toUnsigned(toSigned(memory.getData(addr, InstSize::BYTE), InstSize::BYTE));
        case 0x24u:
            return memory.getData(addr, InstSize::BYTE);
        default:
            return 0u;
    }
}

void InstSimulator::instMemStore(const unsigned addr, const unsigned val, const InstDataBin& inst) {
    switch (inst.getOpCode()) {
        case 0x2Bu:
            memory.setData(addr, val, InstSize::WORD);
            return;
        case 0x29u:
            memory.setData(addr, val, InstSize::HALF);
            return;
        case 0x28u:
            memory.setData(addr, val, InstSize::BYTE);
            return;
        default:
            return;
    }
}

bool InstSimulator::isNop(const InstDataBin& inst) const {
    return !inst.getOpCode() &&
           !inst.getRt() &&
           !inst.getRd() &&
           !inst.getC() &&
           !inst.getFunct();
}

bool InstSimulator::isHalt(const InstDataBin& inst) const {
    return inst.getOpCode() == 0x3Fu;
}

bool InstSimulator::isMemoryLoad(const InstDataBin& inst) const {
    switch (inst.getOpCode()) {
        case 0x23u:
        case 0x21u:
        case 0x25u:
        case 0x20u:
        case 0x24u:
            return true;
        default:
            return false;
    }
}

bool InstSimulator::isMemoryStore(const InstDataBin& inst) const {
    switch (inst.getOpCode()) {
        case 0x2Bu:
        case 0x29u:
        case 0x28u:
            return true;
        default:
            return false;
    }
}

bool InstSimulator::isBranch(const InstDataBin& inst) const {
    return isBranchR(inst) ||
           isBranchI(inst) ||
           isBranchJ(inst);
}

bool InstSimulator::isBranchR(const InstDataBin& inst) const {
    return inst.getInstType() == InstType::R && inst.getFunct() == 0x08u;
}

bool InstSimulator::isBranchI(const InstDataBin& inst) const {
    if (inst.getInstType() != InstType::I) {
        return false;
    }
    return inst.getOpCode() == 0x04u || inst.getOpCode() == 0x05u || inst.getOpCode() == 0x07u;
}

bool InstSimulator::isBranchJ(const InstDataBin& inst) const {
    if (inst.getInstType() != InstType::J) {
        return false;
    }
    return inst.getOpCode() == 0x02u || inst.getOpCode() == 0x03u;
}

} /* namespace inst */
