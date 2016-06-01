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

InstSimulator::InstSimulator(InstSimulator&& that) {
    if (this != &that) {
        this->alive = that.alive;
        this->originalPc = that.originalPc;
        this->currentPc = that.currentPc;
        this->cycle = that.cycle;
        this->snapshot = that.snapshot;
        this->report = that.report;
        this->reg = std::move(that.reg);
        this->iDisk = std::move(that.iDisk);
        this->dDisk = std::move(that.dDisk);
        this->dMem = std::move(that.dMem);
        this->iMem = std::move(that.iMem);
        this->iPageTable = std::move(that.iPageTable);
        this->dPageTable = std::move(that.dPageTable);
        this->iTLB = std::move(that.iTLB);
        this->dTLB = std::move(that.dTLB);
        this->iCache = std::move(that.iCache);
        this->dCache = std::move(that.dCache);
    }
}

InstSimulator::~InstSimulator() {

}

void InstSimulator::init() {
    alive = true;
    originalPc = 0;
    currentPc = 0;
    cycle = 0;
    snapshot = nullptr;
    report = nullptr;
    reg.init();
    for (unsigned i = 0; i < 1024; i += 4) {
        dDisk.setData(i, 0);
        iDisk.setData(i, 0);
        iDisk.setInstruction(i, InstDecoder::decodeInstBin(0));
    }
}

void InstSimulator::loadInstruction(const unsigned* src, const unsigned len, const unsigned pc) {
    this->originalPc = pc;
    for (unsigned i = 0; i < len; ++i) {
        iDisk.setData(pc + (i << 2), src[i]);
        iDisk.setInstruction(pc + (i << 2), InstDecoder::decodeInstBin(src[i]));
    }
}

void InstSimulator::loadData(const unsigned* src, const unsigned len, const unsigned sp) {
    reg.setRegister(29, sp, InstSize::WORD);
    for (unsigned i = 0; i < len; ++i) {
        dDisk.setData(i << 2, src[i]);
    }
}

void InstSimulator::setProperty(const InstParameter& iParam, const InstParameter& dParam) {
    iMem.init(iParam.memSize);
    dMem.init(dParam.memSize);
    iPageTable.init(iParam.pageSize);
    dPageTable.init(dParam.pageSize);
    dTLB.init(dPageTable.entry() >> 2);
    iTLB.init(iPageTable.entry() >> 2);
    iCache.init(iParam.cacheSize, iParam.cacheBlockSize, iParam.cacheSetAssociativity);
    dCache.init(dParam.cacheSize, dParam.cacheBlockSize, dParam.cacheSetAssociativity);
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
    switch (inst.getOpcode()) {
        case 0x23u:
            return dMem.getData(addr, InstSize::WORD);
        case 0x21u:
            return toUnsigned(toSigned(dMem.getData(addr, InstSize::HALF), InstSize::HALF));
        case 0x25u:
            return dMem.getData(addr, InstSize::HALF);
        case 0x20u:
            return toUnsigned(toSigned(dMem.getData(addr, InstSize::BYTE), InstSize::BYTE));
        case 0x24u:
            return dMem.getData(addr, InstSize::BYTE);
        default:
            return 0u;
    }
}

void InstSimulator::instMemStore(const unsigned addr, const unsigned val, const InstDataBin& inst) {
    switch (inst.getOpcode()) {
        case 0x2Bu:
            dMem.setData(addr, val, InstSize::WORD);
            return;
        case 0x29u:
            dMem.setData(addr, val, InstSize::HALF);
            return;
        case 0x28u:
            dMem.setData(addr, val, InstSize::BYTE);
            return;
        default:
            return;
    }
}

bool InstSimulator::isNop(const InstDataBin& inst) const {
    return !inst.getOpcode() &&
           !inst.getRt() &&
           !inst.getRd() &&
           !inst.getC() &&
           !inst.getFunct();
}

bool InstSimulator::isHalt(const InstDataBin& inst) const {
    return inst.getOpcode() == 0x3Fu;
}

bool InstSimulator::isMemoryLoad(const InstDataBin& inst) const {
    switch (inst.getOpcode()) {
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
    switch (inst.getOpcode()) {
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
    return inst.getOpcode() == 0x04u || inst.getOpcode() == 0x05u || inst.getOpcode() == 0x07u;
}

bool InstSimulator::isBranchJ(const InstDataBin& inst) const {
    if (inst.getInstType() != InstType::J) {
        return false;
    }
    return inst.getOpcode() == 0x02u || inst.getOpcode() == 0x03u;
}

InstSimulator& InstSimulator::operator=(InstSimulator&& that) {
    if (this != &that) {
        this->alive = that.alive;
        this->originalPc = that.originalPc;
        this->currentPc = that.currentPc;
        this->cycle = that.cycle;
        this->snapshot = that.snapshot;
        this->report = that.report;
        this->reg = std::move(that.reg);
        this->iDisk = std::move(that.iDisk);
        this->dDisk = std::move(that.dDisk);
        this->dMem = std::move(that.dMem);
        this->iMem = std::move(that.iMem);
        this->iPageTable = std::move(that.iPageTable);
        this->dPageTable = std::move(that.dPageTable);
        this->iTLB = std::move(that.iTLB);
        this->dTLB = std::move(that.dTLB);
        this->iCache = std::move(that.iCache);
        this->dCache = std::move(that.dCache);
    }
    return *this;
}

} /* namespace inst */
