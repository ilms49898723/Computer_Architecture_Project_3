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
    alive = true;
    originalPc = 0;
    currentPc = 0;
    cycle = 0;
    snapshot = nullptr;
    report = nullptr;
    reg.init();
    iDisk.init();
    dDisk.init();
}

void InstSimulator::loadInstruction(const unsigned* src, const unsigned len, const unsigned pc) {
    this->originalPc = pc;
    for (unsigned i = 0; i < len; ++i) {
        iDisk.setData(pc + (i << 2), src[i]);
        iDisk.setInstruction(pc + (i << 2), InstDecoder::decodeInstBin(src[i]));
    }
}

void InstSimulator::loadData(const unsigned* src, const unsigned len, const unsigned sp) {
    reg.setRegister(29, sp);
    for (unsigned i = 0; i < len; ++i) {
        dDisk.setData(i << 2, src[i]);
    }
}

void InstSimulator::setProperty(const InstParameter& iParam, const InstParameter& dParam) {
    this->iParam = iParam;
    this->dParam = dParam;
    this->iTLB.init((1024u / iParam.pageSize) >> 2);
    this->dTLB.init((1024u / dParam.pageSize) >> 2);
    this->iPageTable.init(iParam.pageSize);
    this->dPageTable.init(dParam.pageSize);
    this->iMemory.init(iParam.memSize, iParam.pageSize);
    this->dMemory.init(dParam.memSize, dParam.pageSize);
    this->iCache.init(iParam.cacheSize, iParam.cacheBlockSize, iParam.cacheSetAssociativity);
    this->dCache.init(dParam.cacheSize, dParam.cacheBlockSize, dParam.cacheSetAssociativity);
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

void InstSimulator::search(const unsigned virtualAddr, const InstRoute type) {
    const InstParameter& param = (type == InstRoute::INST) ? iParam : dParam;
    InstTLB& tlb = (type == InstRoute::INST) ? iTLB : dTLB;
    InstPageTable& pageTable = (type == InstRoute::INST) ? iPageTable : dPageTable;
    InstMemory& memory = (type == InstRoute::INST) ? iMemory : dMemory;
    InstCache& cache = (type == InstRoute::INST) ? iCache : dCache;
    InstDisk& disk = (type == InstRoute::INST) ? iDisk : dDisk;
    unsigned vpn = virtualAddr / param.pageSize;
    unsigned ppn = 0;
    auto tlbResult = tlb.lookup(vpn);
    if (tlbResult.second) {
        ppn = tlbResult.first;
        tlb.update(vpn, cycle);
    }
    else {
        auto ptResult = pageTable.find(vpn);
        if (ptResult.second) {
            ppn = ptResult.first;
            tlb.insert(vpn, ppn, cycle);
            memory.update(ppn, cycle);
        }
        else {
            // TODO recheck and complete it
        }
    }
    unsigned physicalAddr = ppn * param.pageSize + virtualAddr % param.pageSize;

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

} /* namespace inst */
